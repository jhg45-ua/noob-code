/*
 * Clasificador SOM — version de referencia CPU (standalone)
 *
 * Algoritmo: para cada patron, recorre todas las neuronas. Para cada neurona
 * calcula la suma de distancias euclideas entre el patron y la propia neurona
 * mas sus vecinas validas (arriba, abajo, izquierda, derecha). La neurona con
 * la suma minima es la ganadora; su etiqueta se asigna al patron.
 *
 * Compilar (Linux/Mac):
 *   gcc -O2 -o som_cpu io.c som_cpu.c -lm
 *
 * Ejecutar:
 *   ./som_cpu <fichero.som> <fichero.pat> [salida.txt]
 *
 * Compilar (Windows, linea de comandos MSVC):
 *   cl /O2 io.c som_cpu.c /link /out:som_cpu.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io.h"

/* -------------------------------------------------------------------------
 * Distancia euclidea entre los pesos de una neurona y un patron.
 * pesos_n apunta al primer componente de la neurona en el array plano.
 * ---------------------------------------------------------------------- */
static float dist_euclidea(const float *pesos_n, const float *patron, int dim)
{
    float acum = 0.0f;
    int d;
    for (d = 0; d < dim; d++) {
        float diff = pesos_n[d] - patron[d];
        acum += diff * diff;
    }
    return sqrtf(acum);
}

/* -------------------------------------------------------------------------
 * Clasifica todos los patrones contra el SOM.
 * etiquetas debe estar pre-reservado con p->num enteros.
 *
 * Complejidad: O(num_patrones * alto * ancho * dim)
 * ---------------------------------------------------------------------- */
void clasificar_cpu(const SOM_t *s, const Patrones_t *p, int *etiquetas)
{
    int np, y, x;

    for (np = 0; np < p->num; np++) {
        const float *patron   = p->datos + np * p->dim;
        float        min_dist = SOM_MAXDIST;

        for (y = 0; y < s->alto; y++) {
            for (x = 0; x < s->ancho; x++) {
                int idx = y * s->ancho + x;
                const float *pn = s->pesos + idx * s->dim;

                /* Distancia propia neurona */
                float dist = dist_euclidea(pn, patron, s->dim);

                /* Vecinos validos: arriba, abajo, izquierda, derecha */
                if (y > 0)
                    dist += dist_euclidea(s->pesos + ((y-1)*s->ancho + x) * s->dim, patron, s->dim);
                if (y < s->alto - 1)
                    dist += dist_euclidea(s->pesos + ((y+1)*s->ancho + x) * s->dim, patron, s->dim);
                if (x > 0)
                    dist += dist_euclidea(s->pesos + (y*s->ancho + (x-1)) * s->dim, patron, s->dim);
                if (x < s->ancho - 1)
                    dist += dist_euclidea(s->pesos + (y*s->ancho + (x+1)) * s->dim, patron, s->dim);

                if (dist < min_dist) {
                    min_dist      = dist;
                    etiquetas[np] = s->labels[idx];
                }
            }
        }
    }
}

/* -------------------------------------------------------------------------
 * main: lee som + patrones, clasifica, imprime por stdout y escribe fichero.
 * ---------------------------------------------------------------------- */
int main(int argc, char **argv)
{
    SOM_t      s;
    Patrones_t p;
    int       *etiquetas;
    int        i;
    const char *salida = "salida.txt";

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <fichero.som> <fichero.pat> [salida.txt]\n", argv[0]);
        return 1;
    }
    if (argc >= 4) salida = argv[3];

    if (leer_som(argv[1], &s) != SOM_OK) {
        fprintf(stderr, "Error al leer SOM: %s\n", argv[1]);
        return 1;
    }
    if (leer_patrones(argv[2], &p) != SOM_OK) {
        fprintf(stderr, "Error al leer patrones: %s\n", argv[2]);
        liberar_som(&s);
        return 1;
    }
    if (s.dim != p.dim) {
        fprintf(stderr, "Error: dimension SOM (%d) != dimension patrones (%d)\n",
                s.dim, p.dim);
        liberar_som(&s);
        liberar_patrones(&p);
        return 1;
    }

    etiquetas = (int *)malloc(p.num * sizeof(int));
    if (!etiquetas) {
        fprintf(stderr, "Error: malloc etiquetas\n");
        liberar_som(&s);
        liberar_patrones(&p);
        return 1;
    }

    printf("SOM: %d x %d  dim=%d\n", s.alto, s.ancho, s.dim);
    printf("Patrones: %d  dim=%d\n", p.num, p.dim);
    printf("Clasificando...\n");

    clasificar_cpu(&s, &p, etiquetas);

    printf("\nResultados:\n");
    for (i = 0; i < p.num; i++)
        printf("  P%d: %d\n", i + 1, etiquetas[i]);

    escribir_resultados(salida, etiquetas, p.num);
    printf("\nResultados escritos en: %s\n", salida);

    free(etiquetas);
    liberar_som(&s);
    liberar_patrones(&p);
    return 0;
}
