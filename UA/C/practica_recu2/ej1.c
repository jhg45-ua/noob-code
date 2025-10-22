//
// Created by Julián Hinojosa Gil on 22/6/24.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMAXTITULO 25
#define kNUMOPINIONES 10
#define kMAXJUEGOS 150

typedef struct
{
    int mes, anyo;
} Date;

typedef struct
{
    char titulo[kMAXTITULO];
    char genero;
    Date fechaLanzamiento;
    int num_opiniones;
    int opiniones[kNUMOPINIONES];
    int clasificacion;
} TFichaVideojuego;

typedef TFichaVideojuego TVideojuegos[kMAXJUEGOS];

void limpiarBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void newGame(TVideojuegos videojuegos, int *numVideojuegos)
{
    printf("\n");

    TFichaVideojuego fichaVideojuego;
    printf("******ALTA VIDEOJUEGO******\n");
    printf("Titulo: ");
    scanf("%[^\n]%*c", fichaVideojuego.titulo);

    printf("Genero (A/C/D): ");
    do
    {
        scanf("%c", &fichaVideojuego.genero);
    } while ((fichaVideojuego.genero != 'A') && (fichaVideojuego.genero != 'C') && (fichaVideojuego.genero != 'D'));

    printf("Fecha de lanzamiento(Mes/Año): ");
    scanf("%d/%d", &fichaVideojuego.fechaLanzamiento.mes, &fichaVideojuego.fechaLanzamiento.anyo);

    printf("Numero de opiniones (1..10): ");
    do
    {
        scanf("%d", &fichaVideojuego.num_opiniones);
    } while (fichaVideojuego.num_opiniones < 1 || fichaVideojuego.num_opiniones > 10);

    for (int i = 0; i < fichaVideojuego.num_opiniones; i++)
    {
        do
        {
            printf("Opinión %d (3,12,18): ", i + 1);
            scanf("%d", &fichaVideojuego.opiniones[i]);
        } while ((fichaVideojuego.opiniones[i] != 3) && (fichaVideojuego.opiniones[i] != 12) && (fichaVideojuego.opiniones[i] != 18));
    }

    fichaVideojuego.clasificacion = 0;

    videojuegos[*numVideojuegos] = fichaVideojuego;
    *numVideojuegos += 1;
    printf("******ALTA VIDEOJUEGOS CORRECTA******\n");
    printf("\n");
}

void establecerClasificacion(TVideojuegos videojuegos, int numVideojuegos)
{
    printf("\n");

    int pos, num_opiniones, suma = 0;
    bool encontrado = false;
    char titulo[kMAXTITULO];
    float media;

    printf("***** CLASIFICAR UN VIDEOJUEGO POR EDAD *****\n");
    printf("Introduce el título del videojuego a clasificar: ");
    scanf("%[^\n]%*c", titulo);

    for (int i = 0; (i < numVideojuegos && !encontrado); i++)
    {
        if (strcmp(titulo, videojuegos[i].titulo) == 0)
        {
            pos = i;
            encontrado = true;
        }
    }

    if (encontrado)
    {
        num_opiniones = videojuegos[pos].num_opiniones;
        for (int j = 0; j < num_opiniones; j++)
            suma += videojuegos[pos].opiniones[j];
        media = (float)(suma / num_opiniones);

        if (media < 12)
            videojuegos[pos].clasificacion = 3;
        if (media < 18)
            videojuegos[pos].clasificacion = 12;
        if (media > 18)
            videojuegos[pos].clasificacion = 18;

        printf("El videojuego <%s> obtiene una clasificación de %d\n", titulo, videojuegos[pos].clasificacion);
        printf("CLASIFICACIÓN DE VIDEOJUEGO CORRECTA\n");
    }
    else
        printf("El videojuego %s NO existe el la base de datos\n", titulo);

    printf("\n");
}

void listarClasificados(TVideojuegos videojuegos, int numVideojuegos)
{
    printf("\n");

    for (int i = 0; i < numVideojuegos; i++)
    {
        if (videojuegos[i].clasificacion != 0)
        {
            printf("Titulo: %s\n", videojuegos[i].titulo);
            printf("Fecha de lanzamiento: %d/%d\n", videojuegos[i].fechaLanzamiento.mes, videojuegos[i].fechaLanzamiento.anyo);
            printf("Clasificación: ");
            switch (videojuegos[i].clasificacion)
            {
            case 3:
                printf("Mayores de 3 años\n");
                break;
            case 12:
                printf("Mayores de 12 años\n");
                break;
            case 18:
                printf("Mayores de 18 años\n");
                break;
            }
        }
    }

    if (numVideojuegos == 0)
        printf("AVISO: Todavía NO se ha clasificado ningún videojuego\n");

    printf("\n");
}

int main()
{
    TVideojuegos videojuegos;
    int numVideojuegos = 0;

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
            limpiarBufferEntrada();
            newGame(videojuegos, &numVideojuegos);
            break;
        case 2:
            limpiarBufferEntrada();
            if (numVideojuegos > 0)
                establecerClasificacion(videojuegos, numVideojuegos);
            else
                printf("No existen videojuegos\n");
            break;
        case 3:
            printf("Opción 3\n");
            limpiarBufferEntrada();
            listarClasificados(videojuegos, numVideojuegos);
            break;
        case 4:
            printf("Finalizando programa...\n");
            return EXIT_SUCCESS;
        default:
            printf("Selecciona una de las 4 opciones");
        }
    }
}