#ifndef FICHEROS_H
#define FICHEROS_H

#include "sim_engine.h"

/**
 * @file ficheros.h
 * @brief Módulo de entrada/salida para la simulación de memoria.
 * 
 * Proporciona funciones para:
 * - Cargar procesos desde archivos de texto
 * - Guardar el estado de la memoria (logging)
 * - Gestión de archivos de log
 * 
 * @author Julian Hinojosa Gil
 * @date 2025
 * @version 1.0
 */

/**
 * @brief Carga los procesos desde un archivo de texto.
 * 
 * Lee el archivo línea por línea y parsea cada proceso con el formato:
 * `<nombre> <t_llegada> <mem_requerida> <t_ejecucion>`
 * 
 * @param[in] ruta Ruta del archivo de entrada
 * @param[out] procesos Array donde se almacenarán los procesos cargados
 * 
 * @return Cantidad de procesos cargados exitosamente
 * @return 0 si hubo error al abrir/leer el archivo
 * 
 * @pre El archivo debe existir y ser legible
 * @pre procesos debe tener espacio para MAX_PROCESOS elementos
 * 
 * @note Usa llamadas POSIX (open, read) según requerimientos de la práctica
 * @warning El buffer interno es de 4KB, archivos más grandes se truncan
 */
int cargar_procesos(const char* ruta, Proceso procesos[]);

/**
 * @brief Guarda el estado actual de la memoria en un archivo de log.
 * 
 * Escribe una línea con formato:
 * `<instante>[dir1, nombre1, tam1] [dir2, nombre2, tam2] ...`
 * 
 * @param[in] ruta Ruta del archivo de salida (se crea si no existe)
 * @param[in] m Puntero a la estructura de memoria a guardar
 * @param[in] instante Instante de tiempo actual de la simulación
 * 
 * @note Usa modo append, no sobrescribe contenido previo
 * @note Permisos del archivo: 0644 (rw-r--r--)
 */
void guardar_estado(const char* ruta, Memoria *m, int instante);

/**
 * @brief Limpia el contenido de un archivo de log.
 * 
 * Abre el archivo con O_TRUNC para borrar su contenido.
 * Si no existe, lo crea vacío.
 * 
 * @param[in] ruta Ruta del archivo a limpiar
 * 
 * @note Llamar al inicio de cada simulación para empezar con log limpio
 */
void limpiar_log(const char* ruta);

#endif // FICHEROS_H