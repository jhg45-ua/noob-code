#include "engine.h"
#include "file_utils.h"
#include <stdio.h>
#include <string.h>

void inicializar_memoria(Memoria *m) {
    m->cant_particiones = 1;

    m->ultimo_indice_asignado = 0;

    m->particiones[0].dir_inicio = 0;
    m->particiones[0].tamano = MEMORIA_TOTAL;
    m->particiones[0].estado = 0;
    strcpy(m->particiones[0].nombre_proceso, "HUECO");
}

void mostrar_estado(Memoria *m) {
    printf("Estado memoria: ");
    for (int i = 0; i < m->cant_particiones; i++) {
        printf("[%d %s %d]", m->particiones[i].dir_inicio, m->particiones[i].nombre_proceso, m->particiones[i].tamano);
    }
    printf("\n");
}

int ocupar_memoria(Memoria *m, int indice_hueco, Proceso p) {
    Particion *hueco = &m->particiones[indice_hueco];
    
    if (hueco->estado != 0 || hueco->tamano < p.mem_requerida) {
        printf("ERROR: no se puede asignar el proceso \n");
        return 1;
    }

    // CASO A: Ajuste Exacto (El proceso ocupa todo el hueco)
    if (hueco->tamano == p.mem_requerida) {
        hueco->estado = 1;
        strcpy(hueco->nombre_proceso, p.nombre);
    } else {
        // CASO B: Hay que dividir (El hueco es más grande)
        // 1. Verificamos que no desbordamos el array
        if (m->cant_particiones >= MAX_PARTICIONES) return 1;

        // 2. DESPLAZAMIENTO: Movemos todo una posición a la derecha
        // desde el final hasta el siguiente al hueco actual
        for (int i = m->cant_particiones; i > indice_hueco + 1; i--) {
            m->particiones[i] = m->particiones[i - 1];
        }

        int tamano_restante = hueco->tamano - p.mem_requerida;
        int dir_nueva = hueco->dir_inicio + p.mem_requerida;

        // 3. Crear el NUEVO hueco restante en la posición siguiente (i+1)
        m->particiones[indice_hueco + 1].dir_inicio = dir_nueva;
        m->particiones[indice_hueco + 1].tamano = tamano_restante;
        m->particiones[indice_hueco + 1].estado = 0; // LIBRE
        strcpy(m->particiones[indice_hueco + 1].nombre_proceso, "HUECO");

        // 4. Actualizar el hueco actual para convertirlo en PROCESO
        hueco->tamano = p.mem_requerida;
        hueco->estado = 1; // OCUPADO
        strcpy(hueco->nombre_proceso, p.nombre);

        // 5. Actualizamos contadores
        m->cant_particiones++;
    }
    // Actualizamos el puntero para Next Fit (para cuando lo implementemos)
    m->ultimo_indice_asignado = indice_hueco;
    
    return 0; // Éxito
}

void compactar(Memoria *m) {
    for (int i = 0; i < m->cant_particiones - 1; i++) {
        if (m->particiones[i].estado == 0 && m->particiones[i+1].estado == 0) {
            m->particiones[i].tamano += m->particiones[i+1].tamano;

            for (int j = i + 1; m->cant_particiones - 1; j++) {
                m->particiones[j] = m->particiones[j+1];
            }

            m->cant_particiones--;
            
            i--;

            printf("[DEBUG] Compactacion realizada\n");
        }
    }
}

bool liberar_proceso(Memoria *m, char *nombre_proceso) {
    for (int i = 0; i < m->cant_particiones; i++) {
        if (m->particiones[i].estado == 1 && strcmp(m->particiones[i].nombre_proceso, nombre_proceso) == 0) {
            m->particiones[i].estado = 0;
            strcpy(m->particiones[i].nombre_proceso, "HUECO");
            printf("[DEBUG] Proceso %s liberado en dir %d\n", nombre_proceso, m->particiones[i].dir_inicio);
            compactar(m);
            return true;
        }
    }
    return false;
}