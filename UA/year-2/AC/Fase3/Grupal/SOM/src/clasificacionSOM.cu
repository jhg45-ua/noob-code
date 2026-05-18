/*----------------------------------------------------------------------------*/
/*  FICHERO:       clasificacionSOM.cu									        */
/*  AUTOR:         Jorge Azorin								       			    */
/*													                            */
/*  RESUMEN												                        */
/*  ~~~~~~~												                        */
/* Ejercicio grupal para la clasificación de patrones de entrada basada         */
/* en SOM utilizando GPUs                                                       */
/*----------------------------------------------------------------------------*/

// includes, project
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include "clasificacionSOM.h"

/*----------------------------------------------------------------------------*/
/* PARÁMETROS DE MICROARQUITECTURA (Para tunear en el Cudathon)               */
/*----------------------------------------------------------------------------*/
// BLOCK_DIM_M3: Define la malla 2D de hilos para el cálculo de distancias.
// En Ampere (RTX 3050) 16x16 suele ir perfecto, pero en Turing (1660 Super)
// probar 32x8 o 32x16 para maximizar el uso de registros.
#define BLOCK_DIM_X_M3 16
#define BLOCK_DIM_Y_M3 16

// BLOCK_SIZE_M4: Define los hilos que participan en la Reducción en Árbol.
// Debe ser potencia de 2 (128, 256, 512). Modificar este valor altera la 
// ocupación (Occupancy) y la cantidad de Memoria Compartida reservada.
#define BLOCK_SIZE_M4 256
#define GRID_SIZE_M4 64

/*----------------------------------------------------------------------------*/
/* Helpers M3: indices row-major y distancia euclidea sobre arrays planos     */
/*----------------------------------------------------------------------------*/
__host__ __device__ inline int IndiceNeuronaRowMajor(int y, int x, int ancho)
{
	// Convenio comun del equipo: neurona (y,x) -> y*ancho + x
	return y * ancho + x;
}

__host__ __device__ inline int IndicePesoRowMajor(int indiceNeurona, int dimension, int componente)
{
	// Layout lineal de pesos: [neurona0(dim), neurona1(dim), ...]
	return indiceNeurona * dimension + componente;
}

__host__ __device__ inline int IndicePesosSoA(int indiceNeurona, int componente, int totalNeuronas)
{
	// Layout SoA (Structure of Arrays): [comp0(neuronas), comp1(neuronas), ...]
	return componente * totalNeuronas + indiceNeurona;
}

static void CopiarSOMLinealSoA(float* pesosLineales)
{
	int totalNeuronas = SOM.Alto * SOM.Ancho;

	for (int y = 0; y < SOM.Alto; y++) {
		for (int x = 0; x < SOM.Ancho; x++) {
			const int indiceNeurona = IndiceNeuronaRowMajor(y, x, SOM.Ancho);
			for (int d = 0; d < SOM.Dimension; d++) {
				// Usamos el nuevo mapeo SoA
				pesosLineales[IndicePesosSoA(indiceNeurona, d, totalNeuronas)] = SOM.Neurona[y][x].pesos[d];
			}
		}
	}
}

__device__ float DistanciaEuclideaNeurona(const float* pesosSOM, const float* patron, int indiceNeurona, int dimension, int totalNeuronas)
{
	float acumulado = 0.0f;
	#pragma unroll 4
	for (int d = 0; d < dimension; ++d)
	{
		const float diferencia = pesosSOM[IndicePesosSoA(indiceNeurona, d, totalNeuronas)] - patron[d];
		acumulado += diferencia * diferencia;
	}
	return sqrtf(acumulado);
}

/*----------------------------------------------------------------------------*/
/* Helper M4: Reducción Ninja a nivel de registros físicos (Warp Shuffle)     */
/*----------------------------------------------------------------------------*/
__device__ inline void warpReduceMin(float& local_min, int& local_idx) 
{
    // Hacemos log2(32) = 5 rondas de intercambio de registros
    for (int offset = 16; offset > 0; offset /= 2) 
    {
        // __shfl_down_sync desplaza el registro 'offset' posiciones hacia abajo
        // 0xffffffff significa que los 32 hilos del warp participan activamente
        float vec_dist = __shfl_down_sync(0xffffffff, local_min, offset);
        int vec_idx    = __shfl_down_sync(0xffffffff, local_idx, offset);
        
        // Cada hilo se queda con el mínimo entre su registro y el de su vecino
        if (vec_dist < local_min) 
        {
            local_min = vec_dist;
            local_idx = vec_idx;
        }
    }
}

/*----------------------------------------------------------------------------*/
/* Kernel M3 (Ximo): distancia(neurona) + distancia(vecindario cruz valido)   */
/* Se encarga de calcular las distancias de cada neurona al patron de entrada */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Kernel M3.1: Cálculo Base (Cero redundancia matemática)                    */
/*----------------------------------------------------------------------------*/
__global__ void KernelDistanciaBase(
	const float* pesosSOM,
	const float* patron,
	int alto,
	int ancho,
	int dimension,
	float* distanciasBase,
	int totalNeuronas)
{
	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= ancho || y >= alto) return;

	const int indiceNeurona = IndiceNeuronaRowMajor(y, x, ancho);

	// Pasamos 'patron' directo en lugar de 'sPatron'
	distanciasBase[indiceNeurona] = DistanciaEuclideaNeurona(pesosSOM, patron, indiceNeurona, dimension, totalNeuronas);
}

/*----------------------------------------------------------------------------*/
/* Kernel M3.2: Patrón Stencil (Suma del vecindario en cruz)                  */
/*----------------------------------------------------------------------------*/
__global__ void KernelSumaVecindario(
	const float* distanciasBase, // Recibe el array ya calculado por el M3.1
	int alto,
	int ancho,
	float* distanciasFinales)
{
	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= ancho || y >= alto) return;

	const int indiceNeurona = IndiceNeuronaRowMajor(y, x, ancho);
	
	// Leemos nuestra propia distancia ya calculada
	float sumaDistancias = distanciasBase[indiceNeurona];

	// Sumamos las distancias precalculadas de los vecinos (Lectura directa de VRAM)
	if (y > 0) sumaDistancias += distanciasBase[IndiceNeuronaRowMajor(y - 1, x, ancho)];
	if (y < alto - 1) sumaDistancias += distanciasBase[IndiceNeuronaRowMajor(y + 1, x, ancho)];
	if (x > 0) sumaDistancias += distanciasBase[IndiceNeuronaRowMajor(y, x - 1, ancho)];
	if (x < ancho - 1) sumaDistancias += distanciasBase[IndiceNeuronaRowMajor(y, x + 1, ancho)];

	// Contrato de salida: puntuación total por neurona
	distanciasFinales[indiceNeurona] = sumaDistancias;
}

static void CopiarTodosPatronesLineales(float* todosPatronesLineales)
{
	for (int p = 0; p < Patrones.Cantidad; ++p)
	{
		for (int d = 0; d < Patrones.Dimension; ++d)
		{
			// Aplanamos: [patron0_d0, patron0_d1..., patron1_d0, patron1_d1...]
			todosPatronesLineales[p * Patrones.Dimension + d] = Patrones.Pesos[p][d];
		}
	}
}

static void CopiarEtiquetasLineal(int* labelsLineales)
{
	for (int y = 0; y < SOM.Alto; ++y)
		for (int x = 0; x < SOM.Ancho; ++x)
			labelsLineales[IndiceNeuronaRowMajor(y, x, SOM.Ancho)] = SOM.Neurona[y][x].label;
}

/*--------------------------------------------------------------------------------*/
/*    Kernel M4 (Julián): Reducción Naive (Búsqueda secuencial en 1 hilo)         */
/* Se encarga de encontrar el índice de la neurona ganadora (con menor distancia) */
/*--------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* FASE 1: Reducción Local por Bloques                                        */
/*----------------------------------------------------------------------------*/
__global__ void KernelReduccionFase1(const float* distancias, int totalNeuronas, float* minDistIntermedio, int* minIdxIntermedio)
{
	__shared__ float sDist[BLOCK_SIZE_M4];
	__shared__ int sIndex[BLOCK_SIZE_M4];

	int tid = threadIdx.x;
	// El hilo global ahora usa gridDim.x para el salto (cubrimos la gráfica entera)
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;

	float min_dist = 1e38f;
	int min_idx = -1;

	// 1. Cada hilo busca el mínimo de los elementos que le tocan
	for (; i < totalNeuronas; i += stride)
	{
		float d = distancias[i];
		if (d < min_dist)
		{
			min_dist = d;
			min_idx = i;
		}
	}

	sDist[tid] = min_dist;
	sIndex[tid] = min_idx;
	__syncthreads();

	// 2. Reducción en árbol (Torneo dentro del bloque)
	for (int s = blockDim.x / 2; s > 0; s >>= 1)
	{
		if (tid < s)
		{
			if (sDist[tid + s] < sDist[tid])
			{
				sDist[tid] = sDist[tid + s];
				sIndex[tid] = sIndex[tid + s];
			}
		}
		__syncthreads();
	}

	// 3. El hilo 0 de CADA BLOQUE escribe su ganador local en el array intermedio
	if (tid == 0)
	{
		minDistIntermedio[blockIdx.x] = sDist[0];
		minIdxIntermedio[blockIdx.x] = sIndex[0];
	}
}

/*----------------------------------------------------------------------------*/
/* Kernel M4 - FASE 2: Reducción Final del ganador absoluto                   */
/*----------------------------------------------------------------------------*/
__global__ void KernelReduccionFase2(const float* minDistIntermedio, const int* minIdxIntermedio, int numBloquesFase1, const int* labelsLineales, int* etiquetasSalida, int np)
{
    // ¡La memoria compartida se reduce drásticamente! Solo necesitamos espacio para 1 ganador por Warp
    __shared__ float sWarpDist[32]; 
    __shared__ int sWarpIndex[32];

    int tid = threadIdx.x;
    int laneId = tid % 32; // Qué hilo soy dentro de mi Warp (0 a 31)
    int warpId = tid / 32; // A qué Warp pertenezco (0 a 7 si el bloque es de 256)

    float min_dist = 1e38f;
    int min_idx = -1;

    // 1. Cada hilo carga su dato desde la memoria global (Resultados de la Fase 1)
    for (int i = tid; i < numBloquesFase1; i += blockDim.x)
    {
        float d = minDistIntermedio[i];
        if (d < min_dist)
        {
            min_dist = d;
            min_idx = minIdxIntermedio[i];
        }
    }

    // 2. Torneo a nivel de registros dentro del Warp (Cero latencia de memoria)
    warpReduceMin(min_dist, min_idx);

    // 3. El hilo 0 de cada Warp escribe SU campeón en la memoria compartida
    if (laneId == 0)
    {
        sWarpDist[warpId] = min_dist;
        sWarpIndex[warpId] = min_idx;
    }
    
    // ---------------------------------------------------------
    // LA ÚNICA BARRERA DE TODO EL KERNEL. Hemos pasado de 8 a 1.
    __syncthreads(); 
    // ---------------------------------------------------------

    // 4. El Warp 0 se encarga de la final
    if (warpId == 0)
    {
        // Los hilos del Warp 0 leen a los campeones. Si no hay campeón, leen infinito.
        min_dist = (tid < (blockDim.x / 32)) ? sWarpDist[laneId] : 1e38f;
        min_idx  = (tid < (blockDim.x / 32)) ? sWarpIndex[laneId] : -1;

        // Último torneo en registros
        warpReduceMin(min_dist, min_idx);

        // 5. El hilo absoluto 0 escribe la sentencia
        if (tid == 0) etiquetasSalida[np] = labelsLineales[min_idx];
    }
}

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// FUNCION A IMPLEMENTAR POR EL GRUPO (paralelización de ClasificacionSOMCPU)
// ---------------------------------------------------------------
// ---------------------------------------------------------------

int ClasificacionSOMGPU()
{
	int estado_final = OKCLAS;

	// 1. Declaración de punteros
	float* hPesosLineales = NULL;
	float* hTodosPatrones = NULL; // Todos los patrones
	int* hLabelsLineales = NULL; 

	float* dPesosLineales = NULL;
	float* dTodosPatrones = NULL; // Todos los patrones en Device
	int* dLabelsLineales = NULL;  // Etiquetas del mapa en Device
	float* d_DistanciasBase = NULL; // Array temporal para el patrón Stencil
	float* dDistancias = NULL;
	int* dEtiquetasSalida = NULL; // Array de resultados en Device
	float* d_minDistIntermedio = NULL;
	int* d_minIdxIntermedio = NULL;

	fprintf(stderr, "Iniciando ClasificacionSOMGPU...\n");
	if (Patrones.Dimension != SOM.Dimension) return ERRORCLASS;

	fprintf(stderr, "SOM: %dx%d, Dimension: %d\n", SOM.Alto, SOM.Ancho, SOM.Dimension);
	const int totalNeuronas = SOM.Alto * SOM.Ancho;
	const size_t bytesPesos = (size_t)totalNeuronas * (size_t)SOM.Dimension * sizeof(float);
	const size_t bytesLabels = (size_t)totalNeuronas * sizeof(int);
	
	// Calculamos el tamaño para TODOS los patrones y TODAS las etiquetas de salida
	const size_t bytesTodosPatrones = (size_t)Patrones.Cantidad * (size_t)SOM.Dimension * sizeof(float);
	const size_t bytesEtiquetasSalida = (size_t)Patrones.Cantidad * sizeof(int);
	const size_t bytesDistancias = (size_t)totalNeuronas * sizeof(float);

	const size_t bytesIntermedios = GRID_SIZE_M4 * sizeof(float);
	const size_t bytesIdxIntermedios = GRID_SIZE_M4 * sizeof(int);

	// 2. Reserva en Host
	hPesosLineales = (float*)malloc(bytesPesos);
	hTodosPatrones = (float*)malloc(bytesTodosPatrones);
	hLabelsLineales = (int*)malloc(bytesLabels);

	if (hPesosLineales == NULL || hTodosPatrones == NULL || hLabelsLineales == NULL) estado_final = ERRORCLASS;

	if (estado_final == OKCLAS)
	{
		// Copiamos TODOS los datos al formato lineal de golpe
		CopiarSOMLinealSoA(hPesosLineales);
		CopiarTodosPatronesLineales(hTodosPatrones); 
		CopiarEtiquetasLineal(hLabelsLineales);

		// 3. Reserva masiva en Device (GPU)
		if (cudaMalloc((void**)&dPesosLineales, bytesPesos) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&dTodosPatrones, bytesTodosPatrones) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&dLabelsLineales, bytesLabels) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&dDistancias, bytesDistancias) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&d_DistanciasBase, bytesDistancias) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&dEtiquetasSalida, bytesEtiquetasSalida) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&d_minDistIntermedio, bytesIntermedios) != cudaSuccess) estado_final = ERRORCLASS;
		if (cudaMalloc((void**)&d_minIdxIntermedio, bytesIdxIntermedios) != cudaSuccess) estado_final = ERRORCLASS;
	}

	if (estado_final == OKCLAS)
	{
		// 4. UNA ÚNICA COPIA MASIVA: Host -> Device
		cudaMemcpy(dPesosLineales, hPesosLineales, bytesPesos, cudaMemcpyHostToDevice);
		cudaMemcpy(dTodosPatrones, hTodosPatrones, bytesTodosPatrones, cudaMemcpyHostToDevice);
		cudaMemcpy(dLabelsLineales, hLabelsLineales, bytesLabels, cudaMemcpyHostToDevice);

		// Uso de los parámetros de microarquitectura definidos en cabecera
		const dim3 blockDimM3(BLOCK_DIM_X_M3, BLOCK_DIM_Y_M3);
		const dim3 gridDimM3((SOM.Ancho + blockDimM3.x - 1) / blockDimM3.x, (SOM.Alto + blockDimM3.y - 1) / blockDimM3.y);

		// 5. El bucle ahora es ultrarrápido: solo encola trabajo en la GPU
		for (int np = 0; np < Patrones.Cantidad && estado_final == OKCLAS; ++np)
		{
			// Puntero aritmético para decirle al kernel dónde empieza el patrón 'np'
			float* dPatronActual = &dTodosPatrones[np * SOM.Dimension];

			// --- FASE M3.1: Cálculo Base (ALU Bound) ---
			KernelDistanciaBase << <gridDimM3, blockDimM3 >> > (
				dPesosLineales, dPatronActual, SOM.Alto, SOM.Ancho, SOM.Dimension, d_DistanciasBase, totalNeuronas);

			// --- FASE M3.2: Stencil (Memory Bound ultrarrápido) ---
			// No necesita memoria compartida
			KernelSumaVecindario<<<gridDimM3, blockDimM3>>>(
				d_DistanciasBase, SOM.Alto, SOM.Ancho, dDistancias);

			// FASE M4.1: Reducción Multibloque (Satura los SMs)
			KernelReduccionFase1<<<GRID_SIZE_M4, BLOCK_SIZE_M4>>>(
				dDistancias, totalNeuronas, d_minDistIntermedio, d_minIdxIntermedio);

			// FASE M4.2: Colapso al resultado final (1 solo bloque rápido)
			KernelReduccionFase2<<<1, BLOCK_SIZE_M4>>>(
				d_minDistIntermedio, d_minIdxIntermedio, GRID_SIZE_M4, dLabelsLineales, dEtiquetasSalida, np);
		}

		// Sincronizamos para asegurar que todos los kernels han terminado
		cudaDeviceSynchronize();

		// 6. UNA ÚNICA COPIA MASIVA DE VUELTA: Device -> Host
		if (cudaMemcpy(EtiquetaGPU, dEtiquetasSalida, bytesEtiquetasSalida, cudaMemcpyDeviceToHost) != cudaSuccess) {
			estado_final = ERRORCLASS;
		}
	}

	// 7. Limpieza de memoria
	if (dDistancias) cudaFree(dDistancias);
	if (d_DistanciasBase) cudaFree(d_DistanciasBase);
	if (dTodosPatrones) cudaFree(dTodosPatrones);
	if (dPesosLineales) cudaFree(dPesosLineales);
	if (dLabelsLineales) cudaFree(dLabelsLineales);
	if (dEtiquetasSalida) cudaFree(dEtiquetasSalida);
	if (d_minDistIntermedio) cudaFree(d_minDistIntermedio);
	if (d_minIdxIntermedio) cudaFree(d_minIdxIntermedio);
	if (hTodosPatrones) free(hTodosPatrones);
	if (hPesosLineales) free(hPesosLineales);
	if (hLabelsLineales) free(hLabelsLineales);

	return estado_final;
}