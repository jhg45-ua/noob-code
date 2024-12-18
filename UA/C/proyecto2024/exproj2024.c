#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KAPUNTADOS 25
#define KTELEFONO 10
#define KNOMBRE 50
#define KSOCIOS 90
#define KACTIVIDADES 42

// Estructuras de datos
typedef struct {
    int horas, minutos;
} THora;

typedef struct {
    char telefono[KTELEFONO], nombre[KNOMBRE];
    int codigo;
} TSocio;
typedef TSocio TSocios[KSOCIOS];

typedef int TApuntados[KAPUNTADOS];

typedef struct {
    int codigo;
    char nombre[KNOMBRE];
    int dia;
    THora hora;
    char tipo;
    TApuntados apuntados;
    int numApuntados;
} TActividad;
typedef TActividad TActividades[KACTIVIDADES];

typedef struct {
    TSocios socios;
    int numSocios;
} TListaSocios;

typedef struct {
    TActividades actividades;
    int numActividades;
} TListaActividades;

typedef struct {
    TListaSocios listaSocios;
    TListaActividades listaActividades;
} TGym;

// Prototipos de funciones
int menu();
void altaSocio(TListaSocios *lista);
int buscarSocio(TListaSocios lista, int codigo);
void bajaSocio(TListaSocios *lista);
void altaActividad(TListaActividades *lista);
void apuntarSocio(TGym *gym);

int main(void)
{
    TGym gym;

    gym.listaActividades.numActividades = 0;
    gym.listaSocios.numSocios = 0;

    int opcion;
    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                altaSocio(&gym.listaSocios);
                break;
            case 2:
                bajaSocio(&gym.listaSocios);
                break;
            case 3:
                altaActividad(&gym.listaActividades);
                break;
            case 4:
                apuntarSocio(&gym);
                break;
            default:
                break;
        }
    } while (opcion != 5);

    return EXIT_SUCCESS;
}

int menu()
{
    int opcion;
    printf("1. Alta socio\n");
    printf("2. Baja socio\n");
    printf("3. Alta actividad\n");
    printf("4. Baja actividad\n");
    printf("5. salir\n");
    printf("Opción: ");
    scanf("%d", &opcion);
    return opcion;
}

// void altaSocio(Tsocios socios, int *numSocios)
void altaSocio(TListaSocios *lista)
{
    TSocio nuevoSocio;
    if (lista->numSocios == KSOCIOS)
        printf("Lista de socios llena\n");
    else {
        printf("Introduce el nombre del nuevo socio: ");
        scanf(" %[^\n]", nuevoSocio.nombre);
        printf("Numero de telefo: ");
        scanf(" %s", nuevoSocio.telefono);

        if (lista->numSocios == 0)
            nuevoSocio.codigo = 1;
        else
            nuevoSocio.codigo = lista->socios[lista->numSocios-1].codigo + 1;

        lista->socios[lista->numSocios] = nuevoSocio;
        lista->numSocios++;
    }
}

int buscarSocio(TListaSocios lista, int codigo)
{
    int pos = -1;

    for (int i = 0; i < lista.numSocios && pos == -1; i++) {
        if (lista.socios[i].codigo == codigo)
            pos = i;
    }
    return pos;
}

void bajaSocio(TListaSocios *lista)
{
    int pos, buscado;

    if (lista->numSocios == 0)
        printf("Lista de socios vacia\n");
    else {
        printf("Introduce el codigo a buscar: ");
        scanf("%d", &buscado);
        pos = buscarSocio(*lista, buscado);
        if (pos == -1)
            printf("Socio no encontrado\n");
        else {
            for (int i = pos; i < lista->numSocios - 1; i++) {
                lista->socios[i] = lista->socios[i+1];
            }
            lista->numSocios--;
        }
    }
}

void altaActividad(TListaActividades *lista)
{
    TActividad nuevaActividad;
    if (lista->numActividades == KACTIVIDADES)
        printf("Lista de actividades completa\n");
    else {
        if (lista->numActividades == 0)
            nuevaActividad.codigo = 0;
        else
            nuevaActividad.codigo = lista->actividades[lista->numActividades-1].codigo + 1;

        printf("1-Lunes ... 7-Domingo: ");
        scanf("%d", &nuevaActividad.dia);
        printf("Hora: ");
        scanf("%d", &nuevaActividad.hora.minutos);
        printf("Minutos: ");
        scanf("%d", &nuevaActividad.hora.minutos);
        printf("(S)pining, (Z)umba, (P)ilates, (C)rosfit\n");
        printf("Tipo de actividad: ");
        scanf(" %c", &nuevaActividad.tipo);

        lista->actividades[lista->numActividades] = nuevaActividad;
        lista->numActividades++;
    }
}

void apuntarSocio(TGym *gym)
{
    int codigo, codSocio, posSocio, pos = -1, i = 0;
    printf("Introduce el codigo de la actividad: ");
    scanf("%d", &codigo);

    while (i < gym->listaActividades.numActividades && pos == -1) {
        if (gym->listaActividades.actividades[i].codigo == codigo)
            pos = i;
        else
            i++;
    }

    if (pos == -1)
        printf("Actividad no entrada\n");
    else {
        if (gym->listaActividades.actividades[pos].numApuntados == KAPUNTADOS)
            printf("Error, lista de apuntados llena\n");
        else {
            printf("Introduce el socio: ");
            scanf("%d", &codSocio);
            posSocio = buscarSocio(gym->listaSocios, codSocio);
            if (posSocio == -1)
                printf("Socio no encontrado\n");
            else {
                gym->listaActividades.actividades[pos].apuntados[gym->listaActividades.actividades[pos].numApuntados] = codSocio;
                gym->listaActividades.actividades[pos].numApuntados++;
            }
        }
    }
}
