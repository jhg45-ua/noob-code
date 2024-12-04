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
    char  prodCode[MAX_PRODUCT_CODE], desc[MAX_DESCRIPTION];
    int   stock, minStock;
    float unitPrice, disc; // Discount percentage (5% -> 5.0)
} TProduct;

// Ticket Line
typedef struct
{
    char  prodCode[MAX_PRODUCT_CODE], desc[MAX_DESCRIPTION];
    int   unitSold;
    float priceUnit, discApplied;
} TticketLine;

// Ticket
typedef struct
{
    int         ticketCode, lineCount;
    char        date[50]; // Date format: string -> YYYY-MM-DD || DD-MM-YYYY
    float       total;
    TticketLine lines[MAX_TICKET_LINES];
} Tticket;

// Function prototypes
void mainMenu();
int  newProduct(TProduct newProduct[], bool debugFlag);

int main(void)
{
    char     option;
    TProduct products[50];

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
                newProduct(products, true);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '2':
                printf("Baja de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '3':
                printf("Modificación de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '4':
                printf("Busqueda de un producto (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '5':
                printf("Crear un nuevo ticket (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '6':
                printf("Buscar/Eliminar un ticket (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '7':
                printf("Comprobar Stock (WIP)\n");
                sleep(SLEEP_TIME);
                system("clear");
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

int newProduct(TProduct newProduct[], bool debugFlag)
{
    char codProd[MAX_PRODUCT_CODE], desc[MAX_DESCRIPTION];
	int stock, minStock;
	float unitPrice, disc;

    printf("Código de producto (Ej: ABC1): ");
    scanf("%s", codProd);
    if (debugFlag)
        printf("(DEBUG) codProd: %s\n", codProd);
    while (getchar() != '\n');

    printf("Descripción: ");
    if (fgets(desc, sizeof(desc), stdin) == NULL) {
        fprintf(stderr, "Error leyendo el input. Pruebe otra vez\n");
        return EXIT_FAILURE;
    }
    int len = strlen(desc);
    if (len > 0 && desc[len - 1] == '\n')
        desc[len - 1] = '\0';
    if (debugFlag)
        printf("(DEBUG): desc: %s\n", desc);

	printf("Introduce el stock actual: ");
	scanf("%d", &stock);

	printf("Introduce el stock minimo: ");
	scanf("%d", &minStock);

	printf("Introduce el precio por unidad: ");
	scanf("%f", &unitPrice);

	printf("Introduce el descuento del producto: ");
	scanf("%f", &disc);

    return EXIT_SUCCESS;
}
