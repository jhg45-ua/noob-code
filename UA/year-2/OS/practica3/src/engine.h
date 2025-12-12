#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

#define MEMORIA_TOTAL 2000
#define UNIDAD_MINIMA 100
#define MAX_PARTICIONES 50
#define MAX_PROCESOS 100

typedef struct {
    char nombre[10];
    int t_llegada;
    int mem_requerida;
    int t_ejecucion;
    int t_final;

    // Variables de control
    int t_restante;
    bool en_memoria;
    bool finalizado;
} Proceso;

typedef struct {
    int dir_inicio;
    int tamano;
    int estado; // 0 -> HUECO || 1 -> PROCESO
    char nombre_proceso[10];
} Particion;


typedef struct {
    Particion particiones[MAX_PARTICIONES];
    int cant_particiones;
    int ultimo_indice_asignado;
} Memoria;

void inicializar_memoria(Memoria *m);
void mostrar_estado(Memoria *m);
int ocupar_memoria(Memoria *m, int indice_hueco, Proceso p);
void compactar(Memoria *m);
bool liberar_proceso(Memoria *m, char *nombre_proceso);

#endif // ENGINE_H