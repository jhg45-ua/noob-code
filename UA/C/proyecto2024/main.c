#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_PRODUCT_CODE 5 // 3 letters + 1 num + \0
#define MAX_DESCRIPTION 30
#define MAX_TICKET_LINES 100
#define SLEEP_TIME 1

// Data types

// Product type
typedef struct
{
    char  prod_code[MAX_PRODUCT_CODE];
    char  desc[MAX_DESCRIPTION];
    int   stock, minStock;
    float unitPrice, disc; // Discount percentage (5% -> 5.0)
} Product;

// Ticket Line
typedef struct
{
    char  prod_code[MAX_PRODUCT_CODE];
    char  desc[MAX_DESCRIPTION];
    int   unitSold;
    float priceUnit, discApplied;
} TicketLine;

// Ticket
typedef struct
{
    int        ticketCode;
    char       date[50]; // Date format: string -> YYYY-MM-DD || DD-MM-YYYY
    float      total;
    TicketLine lines[MAX_TICKET_LINES];
    int        lineCount;
} Ticket;

// Function prototypes
void mainMenu();

int main(void)
{
    char option;

    while (1) {
        mainMenu();

        if (scanf(" %c", &option) != 1) {
            fprintf(stderr, "Error leyendo el input. Pruebe otra vez\n");
            while (getchar() != '\n');
            return EXIT_FAILURE;
        }

        switch (option) {
            case '1':
                printf("Alta de nuevo producto (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '2':
                printf("Baja de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '3':
                printf("Modificación de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '4':
                printf("Busqueda de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '5':
                printf("Crear un nuevo ticket (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '6':
                printf("Buscar/Eliminar un ticket (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case '7':
                printf("Comprobar Stock (WIP)\n");
                sleep(SLEEP_TIME);
                break;
            case 'q':
                printf("Bye....\n");
                sleep(SLEEP_TIME);
                return EXIT_SUCCESS;
            default:
                printf("Ninguna opción seleccionada\n");
                sleep(SLEEP_TIME);
        }
    }

    return EXIT_SUCCESS;
}

void mainMenu()
{
    printf("======== Gestión de Negocio ========\n");
    printf("\t======= MENU =======\n");
    printf("\t  1. Alta producto\n");
    printf("\t  2. Baja producto\n");
    printf("\t  3. Modificación producto\n");
    printf("\t  4. Buscar producto\n");
    printf("\t  5. Crear ticket\n");
    printf("\t  6. Buscar/Eliminar ticket\n");
    printf("\t  7. Comprobar Stock\n");
    printf("\t  q. Salir del programa\n");
    printf("Introduce la opcion: ");
}
