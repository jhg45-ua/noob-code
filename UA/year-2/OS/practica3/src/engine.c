#include "engine.h"
#include "file_utils.h"
#include <stdio.h>
#include <string.h>

/**
 * Inicializa la estructura de memoria con un solo proceso de
 * tipo hueco.
 * @param m Puntero a la estructura de memoria a inicializar
 * @return nada
 */
void inicializar_memoria(Memoria *m) {
    m->cant_particiones = 1;

    m->ultimo_indice_asignado = 0;

    m->particiones[0].dir_inicio = 0;
    m->particiones[0].tamano = MEMORIA_TOTAL;
    m->particiones[0].estado = 0;
    strcpy(m->particiones[0].nombre_proceso, "HUECO");
}

/**
 * Muestra el estado actual de la memoria en consola.
 * @param m Puntero a la estructura de memoria
 * @return nada
 */
void mostrar_estado(Memoria *m) {
    printf("Estado memoria: ");
    for (int i = 0; i < m->cant_particiones; i++) {
        printf("[%d %s %d]", m->particiones[i].dir_inicio, m->particiones[i].nombre_proceso, m->particiones[i].tamano);
    }
    printf("\n");
}

/**
 * Intenta ocupar un hueco de memoria con un proceso.
 * @param m Puntero a la estructura de memoria
 * @param indice_hueco Índice del hueco donde se intentará asignar el proceso
 * @param p Proceso a asignar
 * @return 0 si se asignó correctamente, 1 en caso de error
 */
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

/**
 * Compacta la memoria uniendo huecos adyacentes.
 * @param m Puntero a la estructura de memoria
 * @return nada
 */
void compactar(Memoria *m) {
    // Recorremos hasta el penúltimo elemento
    for (int i = 0; i < m->cant_particiones - 1; i++) {
        // Si la partición actual y la siguiente son huecos, las unimos
        if (m->particiones[i].estado == 0 && m->particiones[i+1].estado == 0) {
            // 1. Sumamos tamaños de las particiones
            m->particiones[i].tamano += m->particiones[i+1].tamano;
            // 2. Movemos todas las particiones siguientes una posición a la izquierda
            for (int j = i + 1; j < m->cant_particiones - 1; j++) {
                m->particiones[j] = m->particiones[j+1];
            }
            // 3. Actualizamos el contador de particiones
            m->cant_particiones--;
            // 4. Retrocedemos el índice para revisar la nueva partición fusionada
            i--;

            printf("[DEBUG] Compactacion realizada\n");
        }
    }
}

/**
 * Libera un proceso de la memoria y compacta si es necesario.
 * @param m Puntero a la estructura de memoria
 * @param nombre_proceso Nombre del proceso a liberar
 * @return true si se liberó correctamente, false si no se encontró el proceso
 */
bool liberar_proceso(Memoria *m, char *nombre_proceso) {
    for (int i = 0; i < m->cant_particiones; i++) {
        // Si encontramos el proceso y esta ocupado, lo liberamos
        if (m->particiones[i].estado == 1 && strcmp(m->particiones[i].nombre_proceso, nombre_proceso) == 0) {
            // 1. Lo convertimos en hueco pasando a estado 0
            m->particiones[i].estado = 0;
            strcpy(m->particiones[i].nombre_proceso, "HUECO");
            printf("[DEBUG] Proceso %s liberado en dir %d\n", nombre_proceso, m->particiones[i].dir_inicio);

            // 2. Compactamos la memoria para unir huecos adyacentes
            compactar(m);

            return true;
        }
    }
    return false;
}

/**
 * Busca un hueco adecuado según el algoritmo especificado.
 * @param m Puntero a la estructura de memoria
 * @param mem_requerida Memoria requerida por el proceso
 * @param tipo_algo Algoritmo de búsqueda (primer hueco o siguiente hueco)
 * @return Índice del hueco encontrado, o -1 si no se encontró ninguno
 */
int buscar_hueco(Memoria *m, int mem_requerida, TipoAlgo tipo_algo) {
    // Algoritmo Primer Hueco
    if (tipo_algo == ALGO_PRIMER_HUECO) {
        // Recorremos todas las particiones buscando el primer hueco que quepa
        for (int i = 0; i < m->cant_particiones; i++) {
            // Si es un hueco libre y cabe el proceso
            if (m->particiones[i].estado == 0 && m->particiones[i].tamano >= mem_requerida) {
                return i; // Devolvemos el índice del hueco encontrado
            }
        }
    }

    // Algoritmo Siguiente Hueco
    if (tipo_algo == ALGO_SIGUIENTE_HUECO) {
        // El punto de partida es el último índice asignado
        int inicio = m->ultimo_indice_asignado;
        // Sacamos el total de particiones para poder hacer la búsqueda circular
        int total = m->cant_particiones;

        // Recorremos todas las particiones empezando desde 'inicio' de forma circular
        for (int j = 0; j < total; j++) {
            // Calculamos el índice real con módulo para la circularidad
            int i = (inicio + j) % total;

            // Si es un hueco libre y cabe el proceso devolvemos su índice en la memoria
            if (m->particiones[i].estado == 0 && m->particiones[i].tamano >= mem_requerida)
                return i;
        }
    }

    return -1;
}

/**
 * Asigna un proceso a la memoria según el algoritmo especificado.
 * @param m Puntero a la estructura de memoria
 * @param p Proceso a asignar
 * @param tipo_algo Algoritmo de búsqueda (primer hueco o siguiente hueco)
 * @return true si se asignó correctamente, false en caso de error
 */
bool asignar_proceso(Memoria *m, Proceso p, TipoAlgo tipo_algo) {
    int pos_mem = buscar_hueco(m, p.mem_requerida, tipo_algo);

    if (pos_mem == -1)
        return false;
    
    return ocupar_memoria(m, pos_mem, p);
}