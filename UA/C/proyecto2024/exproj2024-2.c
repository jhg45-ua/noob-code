#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME 45
#define MAX_TELF 10
#define MAX_CLIENTES 50
#define MAX_CITAS 16

// Estructuras de datos
typedef struct {
    int horas, minutos;
} THora;

typedef struct {
    int  codigo;
    char nombreCompleto[MAX_NAME];
    char telefono[MAX_TELF];
} TCliente;
typedef TCliente TClientes[MAX_CLIENTES];

typedef struct {
    int   codigo;
    char  tipo; // (C)orte, (P)einado, (T)inte
    float precio;
    int   duracion;
} TServicio;

typedef struct {
    char      dia; // (L)unes, (M)artes, (m)iercoles, (J)ueves, (V)iernes
    THora     hora;
    int       codCliente;
    TServicio servicio;
} TCita;
typedef TCita TCitas[MAX_CITAS * 7];

typedef struct {
    TClientes clientes;
    int       numClientes;
} TListaClientes;

typedef struct {
    TCitas citas;
    int    numCitas;
} TListaCitas;

typedef struct {
    TListaClientes listaClientes;
    TListaCitas    listaCitas;
} TPeluqueria;

// Prototipos de funciones
int  menu();
int  buscarClientePos(TListaClientes listaClientes, int codigoCliente);
void altaCliente(TListaClientes* listaClientes);
void bajaCliente(TListaClientes* listaClientes);
void crearCita(TListaCitas* listaCitas, TListaClientes listaClientes);

int main(void)
{
    // Inicialización de la peluquería con datos predefinidos
    TPeluqueria peluqueria = {
        // Clientes
        {
            {{1, "Juan Perez", "123456789"},
             {2, "Ana Lopez", "987654321"}},
            2 // Número de clientes
        },
        // Citas
        {
            {// Cita            // Servicio
             {'L', {9, 30}, 1, {101, 'C', 15.0, 30}},
             {'M', {10, 0}, 2, {102, 'P', 20.0, 45}}},
            2 // Número de citas
        }};

    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                printf("Alta cliente\n");
                altaCliente(&peluqueria.listaClientes);
                break;
            case 2:
                printf("Baja cliente\n");
                bajaCliente(&peluqueria.listaClientes);
                break;
            case 3:
                printf("Crear cita\n");
                crearCita(&peluqueria.listaCitas, peluqueria.listaClientes);
                break;
            case 4:
                printf("Listar clientes con cita\n");
                break;
            case 5:
                printf("Salir\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (opcion != 5);

    return EXIT_SUCCESS;
}

int menu()
{
    int opcion;
    printf("1. Alta cliente\n");
    printf("2. Baja cliente\n");
    printf("3. Crear cita\n");
    printf("4. Listar clientes con cita\n");
    printf("5. salir\n");
    printf("Opción: ");
    scanf("%d", &opcion);
    return opcion;
}

int buscarClientePos(TListaClientes listaClientes, int codigoCliente)
{
    int pos = -1;
    for (int i = 0; i < listaClientes.numClientes && pos == -1; i++) {
        if (listaClientes.clientes[i].codigo == codigoCliente)
            pos = i;
    }
    return pos;
}

void altaCliente(TListaClientes* listaClientes)
{
    TCliente nuevoCliente;
    if (listaClientes->numClientes == MAX_CLIENTES)
        printf("Numero máximo de clientes alcanzado\n");
    else {
        if (listaClientes->numClientes == 0)
            nuevoCliente.codigo = 1;
        else
            nuevoCliente.codigo = listaClientes->clientes[listaClientes->numClientes - 1].codigo + 1;

        printf("Nombre completo del cliente: ");
        scanf(" %[^\n]", nuevoCliente.nombreCompleto);
        printf("Número de contacto: ");
        scanf(" %s", nuevoCliente.telefono);

        listaClientes->clientes[listaClientes->numClientes] = nuevoCliente;
        listaClientes->numClientes++;
    }
}

void bajaCliente(TListaClientes* listaClientes)
{
    int pos, codUsuario;

    printf("Introduce el codigo del cliente: ");
    scanf("%d", &codUsuario);

    pos = buscarClientePos(*listaClientes, codUsuario);
    if (pos > -1) {
        for (int i = pos; pos < listaClientes->numClientes - 1; i++) {
            listaClientes->clientes[i] = listaClientes->clientes[i + 1];
        }
        listaClientes->numClientes--;
        printf("Cliente eliminado con éxito\n");
    }
    else
        printf("No se ha encontrado al cliente\n");
}

void crearCita(TListaCitas* listaCitas, TListaClientes listaClientes)
{
    TCita nuevaCita;
    THora hora;
    int   posCliente, codCliente;

    printf("Dia de la semana (L/M/m/J/V): ");
    scanf(" %c", &nuevaCita.dia);
    printf("Introduce la hora: ");
    scanf("%d", &hora.horas);
    printf("Introduce los minutos: ");
    scanf("%d", &hora.minutos);

    for (int i = 0; i < listaCitas->numCitas; i++) {
        if (listaCitas->citas[i].dia == nuevaCita.dia &&
            listaCitas->citas[i].hora.horas == hora.horas &&
            listaCitas->citas[i].hora.minutos == hora.minutos) {
            printf("Hora ocupada\n");
            return;
        }
    }

    printf("Introduce el codigo de cliente a buscar: ");
    scanf("%d", &codCliente);
    posCliente = buscarClientePos(listaClientes, codCliente);
    if (posCliente == -1)
        printf("El cliente no existe\n");
    else {
        TServicio nuevoServicio;
        printf("Codigo: ");
        scanf("%d", &nuevoServicio.codigo);
        printf("Tipo del servicio: ");
        scanf(" %c", &nuevoServicio.tipo);
        printf("Precio: ");
        scanf("%f", &nuevoServicio.precio);
        printf("Duracion: ");
        scanf("%d", &nuevoServicio.duracion);
        nuevaCita.servicio                      = nuevoServicio;
        nuevaCita.hora                          = hora;
        nuevaCita.codCliente                    = codCliente;
        listaCitas->citas[listaCitas->numCitas] = nuevaCita;
        listaCitas->numCitas++;
    }
}
