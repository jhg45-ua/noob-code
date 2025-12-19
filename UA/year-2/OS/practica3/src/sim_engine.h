#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include <stdbool.h>

/**
 * @file sim_engine.h
 * @brief Declaraciones del motor de simulación de gestión de memoria.
 * @author Julian Hinojosa Gil
 * @date 2025
 */

/** @brief Tamaño total de la memoria simulada */
#define MEMORIA_TOTAL 2000
/** @brief Unidad mínima de asignación de memoria */
#define UNIDAD_MINIMA 100
/** @brief Máximo número de particiones en la memoria */
#define MAX_PARTICIONES 50
/** @brief Máximo número de procesos en la simulación */
#define MAX_PROCESOS 100

/**
 * @brief Estructura que representa un proceso.
 */
typedef struct {
    char nombre[10];            /**< Nombre del proceso */
    int t_llegada;              /**< Tiempo de llegada del proceso */
    int mem_requerida;          /**< Memoria requerida por el proceso */
    int t_ejecucion;            /**< Tiempo de ejecución del proceso */

    // Variables de control
    int t_final;                /**< Tiempo de finalización del proceso */
    int t_restante;             /**< Tiempo restante de ejecución */
    bool en_memoria;            /**< Indica si el proceso está en memoria */
    bool finalizado;            /**< Indica si el proceso ha finalizado */
} Proceso;

/**
 * @brief  que representa una partición de memoria.
 */
typedef struct {
    int dir_inicio;             /**< Dirección de inicio de la partición */
    int tamano;                 /**< Tamaño de la partición */
    int estado;                 /**< Estado de la partición 0 -> HUECO || 1 -> PROCESO  */
    char nombre_proceso[10];    /**< Nombre del proceso asignado o "HUECO" si está libre */
} Particion;

/**
 * @brief Estructura que representa la memoria del sistema.
 */
typedef struct {
    Particion particiones[MAX_PARTICIONES]; /**< Array de particiones de memoria */
    int cant_particiones;                   /**< Cantidad de particiones actuales */
    int ultimo_indice_asignado;             /**< Último índice asignado en particiones */
} Memoria;

/**
 * @brief Tipos de algoritmos de asignación de memoria.
 */
typedef enum {
    ALGO_PRIMER_HUECO,      /**< Algoritmo de Primer Hueco */
    ALGO_SIGUIENTE_HUECO    /**< Algoritmo de Siguiente Hueco */
} TipoAlgo;

/**
 * Inicializa la estructura de memoria con un solo proceso de
 * tipo hueco.
 * @param m Puntero a la estructura de memoria a inicializar
 * @return nada
 */
void inicializar_memoria(Memoria *m);

/**
 * Muestra el estado actual de la memoria en consola.
 * @param m Puntero a la estructura de memoria
 * @return nada
 */
void mostrar_estado(Memoria *m);

/**
 * Intenta ocupar un hueco de memoria con un proceso.
 * @param m Puntero a la estructura de memoria
 * @param indice_hueco Índice del hueco donde se intentará asignar el proceso
 * @param p Proceso a asignar
 * @return 0 si se asignó correctamente, 1 en caso de error
 */
int ocupar_memoria(Memoria *m, int indice_hueco, Proceso p);

/**
 * Compacta la memoria uniendo huecos adyacentes.
 * @param m Puntero a la estructura de memoria
 * @return nada
 */
void compactar(Memoria *m);

/**
 * Libera un proceso de la memoria y compacta si es necesario.
 * @param m Puntero a la estructura de memoria
 * @param nombre_proceso Nombre del proceso a liberar
 * @return true si se liberó correctamente, false si no se encontró el proceso
 */
bool liberar_proceso(Memoria *m, char *nombre_proceso);

/**
 * Busca un hueco adecuado según el algoritmo especificado.
 * @param m Puntero a la estructura de memoria
 * @param mem_requerida Memoria requerida por el proceso
 * @param tipo_algo Algoritmo de búsqueda (primer hueco o siguiente hueco)
 * @return Índice del hueco encontrado, o -1 si no se encontró ninguno
 */
int buscar_hueco(Memoria *m, int mem_requerida, TipoAlgo tipo_algo);

/**
 * Alinea el tamaño solicitado a múltiplos de UNIDAD_MINIMA (100).
 * @param size Tamaño solicitado
 * @return Tamaño alineado
 */
int alinear_size(int size);

/**
 * Asigna un proceso a la memoria según el algoritmo especificado.
 * @param m Puntero a la estructura de memoria
 * @param p Proceso a asignar
 * @param tipo_algo Algoritmo de búsqueda (primer hueco o siguiente hueco)
 * @return true si se asignó correctamente, false en caso de error
 */
bool asignar_proceso(Memoria *m, Proceso p, TipoAlgo tipo_algo);

/**
 * Avanza el tiempo de la simulación, gestionando procesos y memoria.
 * @param m Puntero a la estructura de memoria
 * @param procesos Array de procesos a gestionar
 * @param num_procesos Número de procesos en el array
 * @param reloj_actual Puntero al reloj actual de la simulación
 * @param algo Algoritmo de asignación de memoria a utilizar
 * @return nada
 */
void avanzar_tiempo(Memoria *m, Proceso procesos[], int num_procesos, int *reloj_actual, TipoAlgo algo, const char* ruta_log);

#endif // ENGINE_H