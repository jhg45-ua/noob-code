#ifndef IO_H
#define IO_H

#include <math.h>

/* -------------------------------------------------------------------------
 * Structs con layout plano (row-major) listos para transferir a GPU.
 * Neurona (y, x) -> indice y*ancho + x
 * Pesos neurona i  -> pesos[i*dim .. i*dim+dim-1]
 * Patron p         -> datos[p*dim .. p*dim+dim-1]
 * ---------------------------------------------------------------------- */

typedef struct {
    int    alto;    /* numero de filas      */
    int    ancho;   /* numero de columnas   */
    int    dim;     /* dimension de pesos   */
    float *pesos;   /* [alto*ancho*dim]     */
    int   *labels;  /* [alto*ancho]         */
} SOM_t;

typedef struct {
    int    num;     /* numero de patrones   */
    int    dim;     /* dimension de patron  */
    float *datos;   /* [num*dim]            */
} Patrones_t;

#define SOM_OK      0
#define SOM_ERROR   1
#define SOM_MAXDIST 1e9f

/* Lee fichero .som -> struct plano. Llama a liberar_som() cuando termines. */
int  leer_som(const char *fichero, SOM_t *s);

/* Lee fichero .pat -> struct plano. Llama a liberar_patrones() cuando termines. */
int  leer_patrones(const char *fichero, Patrones_t *p);

/* Escribe etiquetas en fichero con formato "P<n>: <etiqueta>\n". */
void escribir_resultados(const char *fichero, const int *etiquetas, int n);

void liberar_som(SOM_t *s);
void liberar_patrones(Patrones_t *p);

#endif /* IO_H */
