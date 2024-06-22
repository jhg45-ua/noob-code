//
// Created by Julián Hinojosa Gil on 22/6/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMAXTITULO 25
#define kNUMOPINIONES 10
#define kMAXJUEGOS 150


typedef struct { int mes, anyo; }Date;

typedef struct
{
    char titulo[kMAXTITULO];
    char genero;
    Date fechaLanzamiento;
    int num_opiniones;
    int opiniones[kNUMOPINIONES];
    int clasificacion;
}TFichaVideojuego;

typedef TFichaVideojuego TVideojuegos[kMAXJUEGOS];

void newGame(TVideojuegos videojuegos, int numVideojuegos)
{
    fflush(stdin);
    TFichaVideojuego fichaVideojuego;
    printf("******ALTA VIDEOJUEGO******\n");
    printf("Titulo: ");
    scanf("%[^\n]%*c", fichaVideojuego.titulo);

    printf("Genero (A/C/D): ");
    do
    {

        scanf("%c", &fichaVideojuego.genero);
    } while ((fichaVideojuego.genero!='A') && (fichaVideojuego.genero!='C') && (fichaVideojuego.genero!='D'));

    printf("Fecha de lanzamiento(Mes/Año): ");
    scanf("%d/%d", &fichaVideojuego.fechaLanzamiento.mes, &fichaVideojuego.fechaLanzamiento.anyo);

    printf("Numero de opiniones (1..10): ");
    do
    {
        scanf("%d", &fichaVideojuego.num_opiniones);
    } while (fichaVideojuego.num_opiniones < 1 || fichaVideojuego.num_opiniones > 10);

    for (int i = 0; i < fichaVideojuego.num_opiniones; i++)
    {
        printf("Opinión %d (3,12,18): ", i+1);
        do
        {
            scanf("d", &fichaVideojuego.opiniones);
        } while (fichaVideojuego.opiniones[i] != 3 && fichaVideojuego.opiniones[i] != 12 && fichaVideojuego.opiniones[i] != 18);
    }

    fichaVideojuego.clasificacion = 0;

    videojuegos[numVideojuegos] = fichaVideojuego;
    numVideojuegos+=1;
    printf("******ALTA VIDEOJUEGOS CORRECTA******\n");
}

int main()
{
    TVideojuegos videojuegos;
    int numVideojuegos=0;

    while (1)
    {
        int opt;
        printf("1. Introducir un nuevo videojuego\n");
        printf("2. Establecer la clasificación\n");
        printf("3. Listar los videojuegos clasificados\n");
        printf("4. Finalizar la ejecución del programa\n");
        printf("Elige una opción: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            printf("Opción 1\n");
            newGame(videojuegos, numVideojuegos);
            break;
        case 2:
            printf("Opción 2\n");
            break;
        case 3:
            printf("Opción 3\n");
            break;
        case 4:
            printf("Finalizando programa...\n");
            return EXIT_SUCCESS;
        default:
            printf("Selecciona una de las 4 opciones");
        }
    }
}