/*----------------------------------------------------------------------------*/
/*  FICHERO:       clasificacionSOM.h									          */
/*  AUTOR:         Jorge Azorin											  */
/*													                          */
/*  RESUMEN												                      */
/*  ~~~~~~~												                      */
/* Fichero de definiciones y estructuras                                      */
/*    						                                                  */
/*----------------------------------------------------------------------------*/

#ifndef _CLASIFICASOM_H_
#define _CLASIFICASOM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


/*============================================================================ */
/* Constantes											                       */
/*============================================================================ */
#define ERRORCLASS 1
#define OKCLAS    0
#define MAXDIST 10000.0
#define ERROR_CHECK { cudaError_t err; if ((err = cudaGetLastError()) != cudaSuccess) { printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__);}}

/*============================================================================ */
/* Estructuras											                       */
/*============================================================================ */

struct sTNeurona
{
	float* pesos;
	int label;

};
typedef struct sTNeurona TNeurona;


struct sTSOM
{
	int Ancho;
	int Alto;
	int Dimension;
	TNeurona** Neurona;
};
typedef struct sTSOM TSOM;

struct sTPatrones
{
	int Cantidad;
	int Dimension;
	float ** Pesos;
};
typedef struct sTPatrones TPatrones;


/*============================================================================ */
/* Variables Globales										                   */
/*============================================================================ */
extern TSOM SOM;
extern TPatrones Patrones;

extern int* EtiquetaCPU;
extern int* EtiquetaGPU;
	
/*============================================================================ */
/* Prototipos: Memoria e I/O (io_utils.c)									   */
/*============================================================================ */
void BorrarMapa(void);
void BorrarPatrones(void);
int CrearMapa(int Alto, int Ancho, int Dimension);
int CrearPatrones(int Cantidad, int Dimension);
float CalculaDistancia(int y, int x, int np);
int LeerSOM(const char *fichero);
int LeerPatrones(const char *fichero);
int EscribirSOM(int alto, int ancho, int dimension,const char *fichero);
int EscribirPatrones(int cantidad, int dimension, const char *fichero);
void LiberarEtiquetasRobusto(int** etiquetaCPU, int** etiquetaGPU);

/*============================================================================ */
/* Prototipos: Implementacion del problema									   */
/*============================================================================ */
int ClasificacionSOMCPU();
int ClasificacionSOMGPU();


#endif // _CLASIFICASOM_H_
