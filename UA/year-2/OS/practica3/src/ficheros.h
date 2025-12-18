#ifndef FICHEROS_H
#define FICHEROS_H

#include "sim_engine.h"

/**
 * @file ficheros.h
 * @brief Declaraciones para la gestión de ficheros en la simulación de memoria.
 * @author Julian Hinojosa Gil
 * @date 2025
 */

/**
 * Carga los procesos desde un archivo de texto.
 * @param ruta Ruta del archivo de entrada
 * @param procesos Array donde se almacenarán los procesos cargados
 * @return cantidad de procesos cargados
 */
int cargar_procesos(const char* ruta, Proceso procesos[]);

/**
 * Guarda el estado de la memoria en un archivo de texto.
 * @param ruta Ruta del archivo de salida
 * @param m Puntero a la estructura de memoria a inicializar
 * @param instante Instante de tiempo actual
 * @return nada
 */
void guardar_estado(const char* ruta, Memoria *m, int instante);

/**
 * Limpia el contenido de un archivo de texto.
 * @param ruta Ruta del archivo a limpiar
 * @return nada
 */
void limpiar_log(const char* ruta);

#endif // FICHEROS_H