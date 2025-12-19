#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include <stdbool.h>

/**
 * @file sim_engine.h
 * @brief Motor de simulación de gestión de memoria con particiones variables.
 * 
 * Este módulo implementa la lógica central del simulador, incluyendo:
 * - Gestión de particiones de memoria (asignación/liberación)
 * - Algoritmos First Fit y Next Fit
 * - Compactación de huecos adyacentes
 * - Alineación de memoria a múltiplos de UNIDAD_MINIMA
 * 
 * @author Julian Hinojosa Gil
 * @date 2025
 * @version 1.0
 * 
 * @example
 * @code
 * Memoria m;
 * inicializar_memoria(&m);
 * 
 * Proceso p = {"P1", 0, 200, 5, 5, false, false};
 * asignar_proceso(&m, p, ALGO_PRIMER_HUECO);
 * @endcode
 */

/** @defgroup constantes Constantes de Configuración
 *  Valores que determinan los límites del simulador.
 *  @{
 */

/** @brief Tamaño total de la memoria simulada (en unidades) */
#define MEMORIA_TOTAL 2000

/** @brief Unidad mínima de asignación. Toda memoria se alinea a múltiplos de este valor */
#define UNIDAD_MINIMA 100

/** @brief Máximo número de particiones simultáneas en memoria */
#define MAX_PARTICIONES 50

/** @brief Máximo número de procesos que puede manejar la simulación */
#define MAX_PROCESOS 100

/** @} */

/**
 * @brief Estructura que representa un proceso en el simulador.
 * 
 * Contiene toda la información necesaria para gestionar un proceso:
 * - Identificación y tiempos
 * - Requisitos de memoria
 * - Estado actual en la simulación
 */
typedef struct {
    char nombre[10];            /**< Nombre/ID único del proceso (ej: "P1") */
    int t_llegada;              /**< Instante de llegada a la cola de procesos */
    int mem_requerida;          /**< Memoria solicitada (se alineará a UNIDAD_MINIMA) */
    int t_ejecucion;            /**< Tiempo total de ejecución requerido */

    // Variables de control de estado
    int t_final;                /**< Instante en que finalizó (-1 si no ha terminado) */
    int t_restante;             /**< Ticks restantes para completar ejecución */
    bool en_memoria;            /**< true si está cargado en memoria */
    bool finalizado;            /**< true si ya completó su ejecución */
} Proceso;

/**
 * @brief Estructura que representa una partición de memoria.
 * 
 * Una partición puede ser:
 * - Un hueco libre (estado=0, nombre="HUECO")
 * - Un bloque ocupado por un proceso (estado=1)
 */
typedef struct {
    int dir_inicio;             /**< Dirección de inicio en memoria (0 a MEMORIA_TOTAL-1) */
    int tamano;                 /**< Tamaño de la partición (múltiplo de UNIDAD_MINIMA) */
    int estado;                 /**< Estado: 0=HUECO (libre), 1=PROCESO (ocupado) */
    char nombre_proceso[10];    /**< Nombre del proceso o "HUECO" si está libre */
} Particion;

/**
 * @brief Estructura principal que representa la memoria del sistema.
 * 
 * Gestiona un array de particiones que cubren todo el espacio de memoria.
 * Inicialmente contiene una única partición (hueco) de tamaño MEMORIA_TOTAL.
 */
typedef struct {
    Particion particiones[MAX_PARTICIONES]; /**< Array de particiones (huecos y procesos) */
    int cant_particiones;                   /**< Número actual de particiones (1 a MAX_PARTICIONES) */
    int ultimo_indice_asignado;             /**< Último índice usado (para Next Fit) */
} Memoria;

/**
 * @brief Algoritmos de asignación de memoria disponibles.
 * 
 * @see buscar_hueco()
 * @see asignar_proceso()
 */
typedef enum {
    ALGO_PRIMER_HUECO,      /**< First Fit: busca desde el inicio de memoria */
    ALGO_SIGUIENTE_HUECO    /**< Next Fit: busca desde la última posición asignada */
} TipoAlgo;

/**
 * @brief Inicializa la memoria con un único hueco libre.
 * 
 * Configura la memoria con una sola partición de tipo hueco que
 * ocupa todo el espacio disponible (MEMORIA_TOTAL).
 * 
 * @param[out] m Puntero a la estructura de memoria a inicializar
 * 
 * @pre m != NULL
 * @post m->cant_particiones == 1
 * @post m->particiones[0].tamano == MEMORIA_TOTAL
 */
void inicializar_memoria(Memoria *m);

/**
 * @brief Muestra el estado actual de la memoria en consola.
 * 
 * Imprime cada partición en formato: [dir_inicio nombre tamano]
 * 
 * @param[in] m Puntero a la estructura de memoria
 * 
 * @note Solo para depuración/TUI, no afecta el estado
 */
void mostrar_estado(Memoria *m);

/**
 * @brief Ocupa un hueco de memoria con un proceso.
 * 
 * Maneja dos casos:
 * - **Ajuste exacto**: El proceso ocupa todo el hueco
 * - **División**: Se crea una nueva partición con el espacio sobrante
 * 
 * @param[in,out] m Puntero a la estructura de memoria
 * @param[in] indice_hueco Índice del hueco en el array de particiones
 * @param[in] p Proceso a asignar (se usa nombre y mem_requerida)
 * 
 * @return 1 si se asignó correctamente
 * @return 0 si hubo error (hueco ocupado, tamaño insuficiente o array lleno)
 * 
 * @pre 0 <= indice_hueco < m->cant_particiones
 * @pre m->particiones[indice_hueco].estado == 0 (es un hueco)
 * 
 * @warning No verifica si el proceso ya existe en memoria
 */
int ocupar_memoria(Memoria *m, int indice_hueco, Proceso p);

/**
 * @brief Compacta la memoria uniendo huecos adyacentes.
 * 
 * Recorre las particiones y fusiona huecos consecutivos en uno solo.
 * Se llama automáticamente después de liberar un proceso.
 * 
 * @param[in,out] m Puntero a la estructura de memoria
 * 
 * @post No hay dos huecos consecutivos en el array
 * @post cant_particiones puede disminuir
 */
void compactar(Memoria *m);

/**
 * @brief Libera un proceso de la memoria.
 * 
 * Busca el proceso por nombre, lo convierte en hueco y compacta.
 * 
 * @param[in,out] m Puntero a la estructura de memoria
 * @param[in] nombre_proceso Nombre del proceso a liberar
 * 
 * @return true si se encontró y liberó el proceso
 * @return false si el proceso no estaba en memoria
 * 
 * @note Llama automáticamente a compactar() tras liberar
 */
bool liberar_proceso(Memoria *m, char *nombre_proceso);

/**
 * @brief Busca un hueco adecuado según el algoritmo especificado.
 * 
 * Implementa los algoritmos:
 * - **First Fit**: Busca desde el inicio (O(n) peor caso)
 * - **Next Fit**: Busca desde última posición (búsqueda circular)
 * 
 * @param[in] m Puntero a la estructura de memoria
 * @param[in] mem_requerida Memoria requerida (ya alineada)
 * @param[in] tipo_algo Algoritmo a utilizar
 * 
 * @return Índice del hueco encontrado (0 a cant_particiones-1)
 * @return -1 si no hay hueco suficiente
 */
int buscar_hueco(Memoria *m, int mem_requerida, TipoAlgo tipo_algo);

/**
 * @brief Alinea un tamaño a múltiplos de UNIDAD_MINIMA.
 * 
 * Redondea hacia arriba para garantizar que la memoria asignada
 * sea siempre múltiplo de 100.
 * 
 * @param[in] size Tamaño solicitado original
 * 
 * @return Tamaño alineado (múltiplo de UNIDAD_MINIMA)
 * 
 * @par Ejemplos:
 * - alinear_size(50) → 100
 * - alinear_size(100) → 100  
 * - alinear_size(243) → 300
 */
int alinear_size(int size);

/**
 * @brief Asigna un proceso a la memoria.
 * 
 * Realiza el flujo completo de asignación:
 * 1. Alinea la memoria requerida
 * 2. Busca un hueco según el algoritmo
 * 3. Ocupa el hueco encontrado
 * 
 * @param[in,out] m Puntero a la estructura de memoria
 * @param[in] p Proceso a asignar
 * @param[in] tipo_algo Algoritmo de búsqueda a usar
 * 
 * @return true si se asignó correctamente
 * @return false si no hay espacio suficiente
 * 
 * @see alinear_size(), buscar_hueco(), ocupar_memoria()
 */
bool asignar_proceso(Memoria *m, Proceso p, TipoAlgo tipo_algo);

/**
 * @brief Avanza un tick en la simulación.
 * 
 * Ejecuta la lógica de un instante de tiempo:
 * 1. Envejece procesos en memoria (decrementa t_restante)
 * 2. Finaliza procesos cuyo tiempo restante llegó a 0
 * 3. Intenta cargar nuevos procesos de la cola
 * 4. Guarda el estado en el log
 * 5. Incrementa el reloj
 * 
 * @param[in,out] m Puntero a la estructura de memoria
 * @param[in,out] procesos Array de procesos a gestionar
 * @param[in] num_procesos Número de procesos en el array
 * @param[in,out] reloj_actual Puntero al reloj de simulación
 * @param[in] algo Algoritmo de asignación a utilizar
 * @param[in] ruta_log Ruta del archivo de log para guardar estado
 * 
 * @post (*reloj_actual) se incrementa en 1
 */
void avanzar_tiempo(Memoria *m, Proceso procesos[], int num_procesos, int *reloj_actual, TipoAlgo algo, const char* ruta_log);

#endif // ENGINE_H