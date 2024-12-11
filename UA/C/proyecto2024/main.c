#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PRODUCT_CODE 5 // 3 letters + 1 num + \0
#define MAX_DESCRIPTION 30
#define MAX_TICKET_LINES 100
#define MAX_PRODUCT 50
#define SLEEP_TIME 1

/* Data types */

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

/* Function prototypes */
void mainMenu();
int  newProduct(TProduct products[], int* index, bool debugFlag);
bool checkCodeDesc(TProduct products[], int index, const char* productCode, const char* desc);
int  searchProd(TProduct products[], int productCount, const char* productCode, const char* desc);
void showProduct(TProduct products[], int prodCount, const char *prodCode, const char *desc);
void deleteProduct(TProduct products[], int* prodCount);
void checkStock(TProduct products[], int prodCount);

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
                newProduct(products, &prodCount, true);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '2':
                printf("Baja de un producto\n");
                deleteProduct(products, &prodCount);
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
                char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];
                printf("Introduce el código de producto: ");
                scanf(" %[^\n]", searchProdCode);
                printf("Introduce la descripción del producto: ");
                scanf(" %[^\n]", searchProdDesc);
                fflush(stdin);
                showProduct(products, prodCount, searchProdCode, searchProdDesc);
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
                printf("Comprobar Stock\n");
                checkStock(products, prodCount);
                sleep(SLEEP_TIME + 1);
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

int searchProd(TProduct products[], int productCount, const char* productCode, const char* desc)
{
    int i = 0, pos = -1;

    while (pos == -1 && i < productCount) {
        if (strcmp(products[i].prodCode, productCode) == 0 && strcmp(products[i].desc, desc) == 0)
            pos = i;
        else
            i++;
    }
    return pos;
}

int newProduct(TProduct products[], int* prodCount, bool debugFlag)
{
    TProduct newProduct;

    printf("Código de producto (Ej: ABC1): ");
    scanf(" %[^\n]", newProduct.prodCode);

    while (checkCodeDesc(products, *prodCount, newProduct.prodCode, newProduct.desc)) {
        printf("Código de producto ya existente. Introduce otro: ");
        scanf(" %[^\n]", newProduct.prodCode);
    }

    printf("Descripción: ");
    scanf(" %[^\n]", newProduct.desc);

    while (checkCodeDesc(products, *prodCount, newProduct.prodCode, newProduct.desc)) {
        printf("Descripción ya existente. Introduce otra: ");
        scanf(" %[^\n]", newProduct.desc);
    }

    printf("Introduce el stock actual: ");
    scanf("%d", &newProduct.stock);

    printf("Introduce el stock minimo: ");
    scanf("%d", &newProduct.minStock);

    printf("Introduce el precio por unidad: ");
    scanf("%f", &newProduct.unitPrice);

    printf("Introduce el descuento del producto: ");
    scanf("%f", &newProduct.disc);

    products[*prodCount] = newProduct;
    (*prodCount)++;
    printf("Producto guardado correctamente\n");

    int pos = searchProd(products, *prodCount, newProduct.prodCode, newProduct.desc);
    printf("(DEBUG) %d\n", pos);

    return EXIT_SUCCESS;
}

void deleteProduct(TProduct products[], int *prodCount)
{
    char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];
    printf("Introduce el código de producto: ");
    scanf(" %[^\n]", searchProdCode);
    printf("Introduce la descripción del producto: ");
    scanf(" %[^\n]", searchProdDesc);
    fflush(stdin);

    for (int i = 0; i < *prodCount; i++) {
        if (strcmp(products[i].prodCode, searchProdCode) == 0) {
            showProduct(products, *prodCount, searchProdCode, searchProdDesc);

            char sel[5];
            printf("Confirmar borrado (si-s/no-n): ");
            scanf(" %[^\n]", sel);

            if (strcmp("si", sel) == 0 || strcmp("s", sel) == 0) {
                int pos = searchProd(products, *prodCount, searchProdCode, searchProdDesc);
                if (pos == -1)
                    printf("Producto no encontrado\n");
                else {
                    for (int i = pos; i < *prodCount - 1; i++) {
                        products[i] = products[i + 1];
                    }
                    (*prodCount)--;
                }
            } else
                printf("Borrado de producto cancelado\n");
        }
    }
}

void showProduct(TProduct products[], int prodCount, const char *prodCode, const char *desc)
{

    int pos = searchProd(products, prodCount, prodCode, desc);
    printf("(DEBUG) Product position in vector: %d\n", pos);

    if (pos == -1) {
        printf("Error: El producto que buscas no existe\n");
        return;
    }
    else if (pos > -1) {
        printf("Código: %s\n", products[pos].prodCode);
        printf("Descripción: %s\n", products[pos].desc);
        printf("Stock: %d\n", products[pos].stock);
        printf("Stock mínimo: %d\n", products[pos].minStock);
        printf("Precio unitario: %.2f\n", products[pos].unitPrice);
        printf("Descuento: %.2f\n", products[pos].disc);
    }
}

void checkStock(TProduct products[], int prodCount)
{
    if (prodCount == 0)
        printf("No existen productos en la tienda\n");
    else {
        printf("Productos por debajo del stock mínimo\n");
        for (int i = 0; i < prodCount; i++) {
            if (products[i].stock < products[i].minStock) {
                printf("Código: %s\n", products[i].prodCode);
                printf("Descripción: %s\n", products[i].desc);
                printf("Stock: %d\n", products[i].stock);
                printf("Stock mínimo: %d\n", products[i].minStock);
                printf("Precio unitario: %.2f\n", products[i].unitPrice);
                printf("Descuento: %.2f\n", products[i].disc);
                printf("\n");
            }
        }
    }
}
