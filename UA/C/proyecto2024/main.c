#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_PRODUCT_CODE 5 // 3 letters + 1 num + \0
#define MAX_DESCRIPTION 30
#define MAX_TICKET_LINES 100
#define MAX_PRODUCT 50
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
int  newProduct(TProduct products[], int* index, bool debugFlag);
bool checkCodeDesc(TProduct products[], int index, const char* productCode, const char* desc);
void showProduct(TProduct products[], int prodCount);

int main(void)
{
    char     option;
    TProduct products[50];
    int      prodCount = 0;

    while (1) {
        mainMenu();

        if (scanf(" %c", &option) != 1) {
            fprintf(stderr, "Error leyendo el input. Pruebe otra vez\n");
           	fflush(stdin); 
            return EXIT_FAILURE;
        }

        switch (option) {
            case '1':
                printf("Alta de nuevo producto\n");
				fflush(stdin);	
                newProduct(products, &prodCount, true);
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
                printf("Busqueda de un producto\n");
				fflush(stdin);
				showProduct(products, prodCount);
				printf("Presione cualquier tecla para continuar");
				getchar();
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

bool checkCodeDesc(TProduct products[], int index, const char* productCode, const char* desc)
{
    for (int i = 0; i < index; i++) {
        if (strcmp(products[i].prodCode, productCode) == 0)
            return true;
        if (strcmp(products[i].desc, desc) == 0)
            return true;
    }
    return false;
}

int newProduct(TProduct products[], int* index, bool debugFlag)
{
    TProduct newProduct;

    printf("Código de producto (Ej: ABC1): ");
	fgets(newProduct.prodCode, sizeof(newProduct.prodCode), stdin);
	fflush(stdin);	

    while (checkCodeDesc(products, *index, newProduct.prodCode, newProduct.desc)) {
        printf("Código de producto ya existente. Introduce otro: ");
        scanf("%4s", newProduct.prodCode);
		fflush(stdin);	
    }

    printf("Descripción: ");

    if (fgets(newProduct.desc, sizeof(newProduct.desc), stdin) != NULL) {
        size_t len = strlen(newProduct.desc);
        if (len > 0 && newProduct.desc[len - 1] == '\n')
            newProduct.desc[len - 1] = '\0';
    }

    while (checkCodeDesc(products, *index, newProduct.prodCode, newProduct.desc)) {
        printf("Descripción ya existente. Introduce otra: ");
        if (fgets(newProduct.desc, sizeof(newProduct.desc), stdin) != NULL) {
        	size_t len = strlen(newProduct.desc);
            if (len > 0 && newProduct.desc[len - 1] == '\n')
                newProduct.desc[len - 1] = '\0';
        }
    }

    printf("Introduce el stock actual: ");
    scanf("%d", &newProduct.stock);

    printf("Introduce el stock minimo: ");
    scanf("%d", &newProduct.minStock);

    printf("Introduce el precio por unidad: ");
    scanf("%f", &newProduct.unitPrice);

    printf("Introduce el descuento del producto: ");
    scanf("%f", &newProduct.disc);

    products[*index] = newProduct;
    (*index)++;
    printf("Producto guardado correctamente\n");

    return EXIT_SUCCESS;
}

void showProduct(TProduct products[], int prodCount)
{
	char searchProdCode[MAX_PRODUCT_CODE];
	printf("Introduce el código de producto: ");
	fgets(searchProdCode, sizeof(searchProdCode), stdin);
	fflush(stdin);

	for (int i = 0; i < prodCount; i++) {
		if (strcmp(products[i].prodCode, searchProdCode) == 0) {
			printf("Código: %s\n", products[i].prodCode);
			printf("Descripción: %s\n", products[i].desc);
			printf("Stock: %d\n", products[i].stock);
			printf("Stock mínimo: %d\n", products[i].minStock);
			printf("Precio unitario: %.2f\n", products[i].unitPrice);
			printf("Descuento: %.2f\n", products[i].disc);
		}
		else {	
			printf("Error: El producto que buscas no existe\n");
			return;
		}
	}

}
