#ifndef FICHEROS_H
#define FICHEROS_H

#include "sim_engine.h"


int cargar_procesos(const char* ruta, Proceso procesos[]);

void guardar_estado(const char* ruta, Memoria *m, int instante);

void limpiar_log(const char* ruta);

#endif // FICHEROS_H