#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

/* -------------------------------------------------------------------------
 * Formato fichero .som
 *   Alto: <int>
 *   Ancho: <int>
 *   Dimension: <int>
 *   N<x>,<y>: <w0> <w1> ... <wdim-1>     <- los ids N/L se ignoran
 *   L<x>,<y>: <label>
 *   ...  orden en fichero: x varia lento (1..ancho), y varia rapido (1..alto)
 *
 * El harness del profesor lee en el mismo orden (bucle exterior=x, interior=y)
 * y almacena en Neurona[y][x]. Nosotros almacenamos en plano: indice = y*ancho+x
 * ---------------------------------------------------------------------- */
int leer_som(const char *fichero, SOM_t *s)
{
    FILE *f;
    int x, y, d, nx, ny;

    memset(s, 0, sizeof(*s));
    if ((f = fopen(fichero, "r")) == NULL) return SOM_ERROR;

    if (fscanf(f, "Alto: %d\n",      &s->alto)  < 1) goto fail;
    if (fscanf(f, "Ancho: %d\n",     &s->ancho) < 1) goto fail;
    if (fscanf(f, "Dimension: %d\n", &s->dim)   < 1) goto fail;
    if (feof(f)) goto fail;

    {
        int total = s->alto * s->ancho;
        s->pesos  = (float *)malloc((size_t)total * s->dim * sizeof(float));
        s->labels = (int *)  malloc((size_t)total * sizeof(int));
        if (!s->pesos || !s->labels) goto fail;

        int count = 0;
        for (x = 0; x < s->ancho && !feof(f); x++) {
            for (y = 0; y < s->alto && !feof(f); y++) {
                int idx = y * s->ancho + x;
                fscanf(f, "N%d,%d:", &nx, &ny);
                for (d = 0; d < s->dim - 1; d++)
                    fscanf(f, " %f", &s->pesos[idx * s->dim + d]);
                fscanf(f, " %f\n", &s->pesos[idx * s->dim + s->dim - 1]);
                fscanf(f, "L%d,%d: %d\n", &nx, &ny, &s->labels[idx]);
                count++;
            }
        }
        fclose(f);
        if (count != total) { liberar_som(s); return SOM_ERROR; }
    }
    return SOM_OK;

fail:
    fclose(f);
    liberar_som(s);
    return SOM_ERROR;
}

/* -------------------------------------------------------------------------
 * Formato fichero .pat
 *   Numero: <int>
 *   Dimension: <int>
 *   P<n>: <w0> <w1> ... <wdim-1>         <- id P se ignora
 * ---------------------------------------------------------------------- */
int leer_patrones(const char *fichero, Patrones_t *p)
{
    FILE *f;
    int i, d, np;

    memset(p, 0, sizeof(*p));
    if ((f = fopen(fichero, "r")) == NULL) return SOM_ERROR;

    if (fscanf(f, "Numero: %d\n",    &p->num) < 1) goto fail;
    if (fscanf(f, "Dimension: %d\n", &p->dim) < 1) goto fail;
    if (feof(f)) goto fail;

    p->datos = (float *)malloc((size_t)p->num * p->dim * sizeof(float));
    if (!p->datos) goto fail;

    {
        int count = 0;
        for (i = 0; i < p->num && !feof(f); i++) {
            fscanf(f, "P%d:", &np);
            for (d = 0; d < p->dim - 1; d++)
                fscanf(f, " %f", &p->datos[i * p->dim + d]);
            fscanf(f, " %f\n", &p->datos[i * p->dim + p->dim - 1]);
            count++;
        }
        fclose(f);
        if (count != p->num) { liberar_patrones(p); return SOM_ERROR; }
    }
    return SOM_OK;

fail:
    fclose(f);
    liberar_patrones(p);
    return SOM_ERROR;
}

/* -------------------------------------------------------------------------
 * Escribe "P<n>: <etiqueta>" por linea en fichero.
 * ---------------------------------------------------------------------- */
void escribir_resultados(const char *fichero, const int *etiquetas, int n)
{
    int i;
    FILE *f = fopen(fichero, "w");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir '%s' para escritura\n", fichero);
        return;
    }
    for (i = 0; i < n; i++)
        fprintf(f, "P%d: %d\n", i + 1, etiquetas[i]);
    fclose(f);
}

void liberar_som(SOM_t *s)
{
    if (s->pesos)  { free(s->pesos);  s->pesos  = NULL; }
    if (s->labels) { free(s->labels); s->labels = NULL; }
}

void liberar_patrones(Patrones_t *p)
{
    if (p->datos) { free(p->datos); p->datos = NULL; }
}
