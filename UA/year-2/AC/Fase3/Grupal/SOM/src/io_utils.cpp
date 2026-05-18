#include <stdio.h>
#include <stdlib.h>
#include "clasificacionSOM.h"

void BorrarMapa(void)
{
	int i;
	if (SOM.Neurona != NULL)
	{
		for (i = 0; i < SOM.Alto; i++)
			if (SOM.Neurona[i] != NULL) free(SOM.Neurona[i]);

		free(SOM.Neurona);
		SOM.Neurona = NULL;
	}
}

void BorrarPatrones(void)
{
	int i;
	if (Patrones.Pesos != NULL)
	{
		for (i = 0; i < Patrones.Cantidad; i++)
		    if (Patrones.Pesos[i] != NULL) free(Patrones.Pesos[i]);

		free(Patrones.Pesos);
		Patrones.Pesos = NULL;
	}
}

int CrearMapa(int Alto, int Ancho, int Dimension)
{
	int i,j;
	SOM.Alto = Alto;
	SOM.Ancho = Ancho;
	SOM.Dimension = Dimension; // FIX NUESTRO
	SOM.Neurona = (TNeurona**)malloc(SOM.Alto*sizeof(TNeurona*));
	if (SOM.Neurona == NULL) return ERRORCLASS;
	for (j = 0; j < SOM.Alto; j++)
	{
		SOM.Neurona[j] = (TNeurona*)malloc(SOM.Ancho*(int)sizeof(TNeurona));
		if (SOM.Neurona[j] == NULL)
		{
			BorrarMapa();
			return ERRORCLASS;
		}
		for (i = 0; i < SOM.Ancho; i++)
			SOM.Neurona[j][i].pesos = (float*)malloc(Dimension*(int)sizeof(float));
	}
	return OKCLAS;
}

int CrearPatrones(int Cantidad, int Dimension)
{
	int j;
	Patrones.Cantidad=Cantidad;
	Patrones.Dimension=Dimension;
	Patrones.Pesos = (float**)malloc(Cantidad*sizeof(float*));
	for (j = 0; j < Cantidad; j++)
	{
		Patrones.Pesos[j] = (float*)malloc(Dimension*(int)sizeof(float));
		if (Patrones.Pesos[j] == NULL)
		{
			BorrarPatrones();
			return ERRORCLASS;
		}
		
	}
	return OKCLAS;
}

float CalculaDistancia(int y, int x, int np)
{
	float distancia=0;
	if (y>=0 && y<SOM.Alto && x>=0 && x<SOM.Ancho)
	{
		for (int i=0;i<Patrones.Dimension;i++)
		{
			float diferencia = SOM.Neurona[y][x].pesos[i]-Patrones.Pesos[np][i];
			distancia += diferencia*diferencia;
		}
		distancia = sqrtf(distancia);
	}
	return distancia;
}

/*----------------------------------------------------------------------------*/
/*	Función:  LeerSOM(char *fichero)						             	  */
/*													                          */
/*	          Lee la estructura del SOM con formato .SOM   					  */
/*							!!!!! NO TOCAR !!!!!						      */
/*----------------------------------------------------------------------------*/
int LeerSOM(const char *fichero)
{
	int i, j, ndim, count;		/* Variables de bucle */
	int alto,ancho;		/* Variables de tamaño del mapa */
	FILE *fpin; 			/* Fichero */
	int nx,ny,lx,ly,label,dimension;
	float pesos;

	/* Apertura de Fichero */
	if ((fpin = fopen(fichero, "r")) == NULL) return ERRORCLASS;
	/* Lectura de cabecera */
	if (fscanf(fpin, "Alto: %d\n", &alto)<0) return ERRORCLASS;
	if (fscanf(fpin, "Ancho: %d\n", &ancho)<0) return ERRORCLASS;
	if (fscanf(fpin, "Dimension: %d\n", &dimension)<0) return ERRORCLASS;
	if (feof(fpin)) return ERRORCLASS;

	if (CrearMapa(alto, ancho, dimension) == ERRORCLASS) return ERRORCLASS;
	/* Lectura del SOM */
	count = 0;
	for (i = 0; i<ancho; i++)
	{
		for (j = 0; j<alto; j++)
		{
			if (!feof(fpin))
			{
				fscanf(fpin, "N%d,%d:", &nx, &ny);
				for (ndim = 0; ndim<dimension-1;ndim++)
				{
			        fscanf(fpin, " %f", &pesos);
				    SOM.Neurona[j][i].pesos[ndim] = pesos;
				}
				fscanf(fpin, " %f\n", &pesos);
				SOM.Neurona[j][i].pesos[ndim] = pesos;
				
				fscanf(fpin, "L%d,%d: %d\n", &lx, &ly, &label);
				SOM.Neurona[j][i].label=label;
			
				count++;
			}
			else break;
		}
	}
	fclose(fpin);
	if (count != ancho*alto) return ERRORCLASS;
	return OKCLAS;
}

/*----------------------------------------------------------------------------*/
/*	Función:  LeerPatrones(char *fichero)						              */
/*													                          */
/*	          Lee los patrones de un fichero de entrada .pat   			      */
/*							!!!!! NO TOCAR !!!!!						      */
/*----------------------------------------------------------------------------*/
int LeerPatrones(const char *fichero)
{
	int i, ndim, count;		/* Variables de bucle */
	int cantidad,dimension;		/* Variables de tamaño de los patrones */
	FILE *fpin; 			/* Fichero */

	int np;
	float pesos;

	/* Apertura de Fichero */
	if ((fpin = fopen(fichero, "r")) == NULL) return ERRORCLASS;
	/* Lectura de cabecera */
	if (fscanf(fpin, "Numero: %d\n", &cantidad)<0) return ERRORCLASS;
	if (fscanf(fpin, "Dimension: %d\n", &dimension)<0) return ERRORCLASS;
	if (feof(fpin)) return ERRORCLASS;
	
	if (CrearPatrones(cantidad, dimension) == ERRORCLASS) return ERRORCLASS;
	/* Lectura de patrones */
	count = 0;
	for (i = 0; i<cantidad; i++)
	{
	  	if (!feof(fpin))
		{
			fscanf(fpin, "P%d:", &np);
				for (ndim = 0; ndim<dimension-1;ndim++)
				{
			        fscanf(fpin, " %f", &pesos);
					Patrones.Pesos[i][ndim] = pesos;
				}
				fscanf(fpin, " %f\n", &pesos);
				Patrones.Pesos[i][ndim] = pesos;
				
					
				count++;
			}
			else break;
	}
	
	fclose(fpin);
	if (count != cantidad) return ERRORCLASS;
	return OKCLAS;
}

/*----------------------------------------------------------------------------*/
/*	Función:  EscribirSOM(char *fichero)						              */
/*													                          */
/*	          Escribe la estructura del SOM en un fichero de salida .SOM   	  */
/*							!!!!! NO TOCAR !!!!!						      */
/*----------------------------------------------------------------------------*/
int EscribirSOM(int alto, int ancho, int dimension,const char *fichero)
{
	int i, j, ndim, count;		/* Variables de bucle */
	
	FILE *fpin; 			/* Fichero */
	int label;
	float pesos;

	/* Apertura de Fichero */
	if ((fpin = fopen(fichero, "w")) == NULL) return ERRORCLASS;
	/* Lectura de cabecera */
	if (fprintf(fpin, "Alto: %d\n", alto)<0) return ERRORCLASS;
	if (fprintf(fpin, "Ancho: %d\n", ancho)<0) return ERRORCLASS;
	if (fprintf(fpin, "Dimension: %d\n", dimension)<0) return ERRORCLASS;
	if (feof(fpin)) return ERRORCLASS;

	count = 0;
	for (i = 0; i<alto; i++)
	{
		for (j = 0; j<ancho; j++)
		{
			if (!feof(fpin))
			{
				fprintf(fpin, "N%d,%d:", i+1, j+1);
				for (ndim = 0; ndim<dimension-1;ndim++)
				{
					pesos=(rand()%1000)/10.0;
			        fprintf(fpin, " %lf", pesos);
				}				
				pesos=(rand()%1000)/10;
				fprintf(fpin, " %lf\n", &pesos);
				
				label=(rand()%5);
				fprintf(fpin, "L%d,%d: %d\n", i+1, j+1, label);
				
				count++;
			}
			else break;
		}
	}
	fclose(fpin);
	if (count != ancho*alto) return ERRORCLASS;
	return OKCLAS;
}


/*----------------------------------------------------------------------------*/
/*	Función:  EscribirPatrones(char *fichero)						          */
/*													                          */
/*	          Escribe los patrones en un fichero de salida .pat   	          */
/*							!!!!! NO TOCAR !!!!!						      */
/*----------------------------------------------------------------------------*/
int EscribirPatrones(int cantidad, int dimension,const char *fichero)
{
	int i, ndim, count;		/* Variables de bucle */
	
	FILE *fpin; 			/* Fichero */

	// int np;				// FIX NUESTRO: np no se usa, lo eliminamos para evitar confusión
	float pesos;

	/* Apertura de Fichero */
	if ((fpin = fopen(fichero, "w")) == NULL) return ERRORCLASS;
	/* Lectura de cabecera */
	if (fprintf(fpin, "Numero: %d\n", cantidad)<0) return ERRORCLASS;
	if (fprintf(fpin, "Dimension: %d\n", dimension)<0) return ERRORCLASS;
	if (feof(fpin)) return ERRORCLASS;
	
	/* Lectura de patrones */
	count = 0;
	for (i = 0; i<cantidad; i++)
	{
	  	if (!feof(fpin))
		{
			fprintf(fpin, "P%d:", i+1);
				for (ndim = 0; ndim<dimension-1;ndim++)
				{
					pesos=(rand()%1000)/10.0;
			        fprintf(fpin, " %lf", pesos);
				}
				pesos=(rand()%1000)/10;
				fprintf(fpin, " %lf\n", pesos);
					
					
				count++;
			}
			else break;
	}
	
	fclose(fpin);
	if (count != cantidad) return ERRORCLASS;
	return OKCLAS;
}

/*
 * Copia robusta preservada para rama de desarrollo:
 * centraliza la liberacion correcta de EtiquetaCPU/EtiquetaGPU y
 * anula punteros para evitar dobles liberaciones accidentales.
 */
void LiberarEtiquetasRobusto(int** etiquetaCPU, int** etiquetaGPU)
{
	if (etiquetaCPU != NULL && *etiquetaCPU != NULL)
	{
		free(*etiquetaCPU);
		*etiquetaCPU = NULL;
	}
	if (etiquetaGPU != NULL && *etiquetaGPU != NULL)
	{
		free(*etiquetaGPU);
		*etiquetaGPU = NULL;
	}
}