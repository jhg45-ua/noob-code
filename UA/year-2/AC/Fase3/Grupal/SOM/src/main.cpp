#include <stdio.h>
#include <stdlib.h>
#include "clasificacionSOM.h"

#include <cuda_runtime.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    typedef LARGE_INTEGER timeStamp;
#else
    #include <sys/time.h>
    #include <stddef.h>
#endif

// --- Definición Real de las Variables Globales ---
TSOM SOM;
TPatrones Patrones;
int* EtiquetaCPU = NULL;
int* EtiquetaGPU = NULL;

// --- Funciones de Adaptación para Medición de Tiempos ---
/* Funciones auxiliares */
double getTime()
{
#if defined(_WIN32) || defined(_WIN64)
    // Implementación original para Windows
    timeStamp start;
    timeStamp dwFreq;
    QueryPerformanceFrequency(&dwFreq);
    QueryPerformanceCounter(&start);
    return double(start.QuadPart) / double(dwFreq.QuadPart);
#else
    // Implementación para sistemas POSIX (Linux/macOS)
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
#endif
}

////////////////////////////////////////////////////////////////////////////////
/*                           PROGRAMA PRINCIPAL                               */
/*							!!!!! NO TOCAR !!!!!						      */
////////////////////////////////////////////////////////////////////////////////
void runTest(int argc, char** argv)
{

  	double gpu_start_time, gpu_end_time;
	double cpu_start_time, cpu_end_time;

	//EscribirSOM(32,32,64,"peq.som");
	//EscribirPatrones(1024,64,"peq.pat");
	/* Numero de argumentos */
	if (argc != 3)
	{
		fprintf(stderr, "Numero de parametros incorecto\n");
		fprintf(stderr, "Uso: %s superficie pasossim\n", argv[0]);
		return;
	}

	/* Apertura de Fichero */
	printf("Clasificacion basada en SOM...\n");
	/* Mapa SOM */
	if (LeerSOM((char *)argv[1]) == ERRORCLASS)
	{
		fprintf(stderr, "Lectura de SOM incorrecta\n");
		return;
	}
	/* Patrones */
	if (LeerPatrones((char *)argv[2]) == ERRORCLASS)
	{
		fprintf(stderr, "Lectura de patrones incorrecta\n");
		return;
	}
	
	// Creación etiquetas resultados para versiones CPU y GPU

	EtiquetaCPU = (int*)malloc(Patrones.Cantidad*sizeof(int));
	EtiquetaGPU = (int*)malloc(Patrones.Cantidad*sizeof(int));
	
	/* Algoritmo a paralelizar */
	cpu_start_time = getTime();
	if (ClasificacionSOMCPU() == ERRORCLASS)
	{
		fprintf(stderr, "Clasificacion CPU incorrecta\n");
		BorrarMapa();
		LiberarEtiquetasRobusto(&EtiquetaCPU, &EtiquetaGPU);
		exit(1);
	}
	cpu_end_time = getTime();
	cudaSetDevice(0);
	/* Algoritmo a implementar */
	gpu_start_time = getTime();
	if (ClasificacionSOMGPU() == ERRORCLASS)
	{
		fprintf(stderr, "Clasificacion GPU incorrecta\n");
		BorrarMapa();
		LiberarEtiquetasRobusto(&EtiquetaCPU, &EtiquetaGPU);
		return;
	}
	cudaDeviceSynchronize();
	gpu_end_time = getTime();
	// Comparación de corrección
	int comprobar = OKCLAS;
	for (int i = 0; i<Patrones.Cantidad; i++)
	{
		if ((EtiquetaCPU[i] != EtiquetaGPU[i]))
		{
			comprobar = ERRORCLASS;
			fprintf(stderr, "Fallo en la clasificacion del patron %d, valor correcto %d\n", i, EtiquetaCPU[i]);
		}
	}
	// Impresion de resultados
	if (comprobar == OKCLAS)
	{
		printf("Clasificacion correcta!\n");

	}
	// Impresión de resultados
	printf("Tiempo ejecucion GPU : %fs\n", \
		gpu_end_time - gpu_start_time);
	printf("Tiempo de ejecucion en la CPU : %fs\n", \
		cpu_end_time - cpu_start_time);
	printf("Se ha conseguido un factor de aceleracion %fx utilizando CUDA\n", (cpu_end_time - cpu_start_time) / (gpu_end_time - gpu_start_time));
	// Limpieza de Neuronas
	BorrarMapa();
	BorrarPatrones();
	LiberarEtiquetasRobusto(&EtiquetaCPU, &EtiquetaGPU);
	return;
}

int main(int argc, char** argv)
{
	runTest(argc, argv);
	// getchar();

	return 0;
}