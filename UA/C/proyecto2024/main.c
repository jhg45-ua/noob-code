#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PRODUCT_CODE 5 // 3 letters + 1 num + \0
#define MAX_DESCRIPTION 30
#define MAX_TICKET_LINES 10
#define MAX_TICKET 100
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

int  newProduct(TProduct products[], int* index, bool debugFlag);
void deleteProduct(TProduct products[], int* prodCount);
void modProd(TProduct products[], int prodCount);
void checkStock(TProduct products[], int prodCount);
void mainMenu();
bool checkCodeDesc(TProduct products[], int index, const char* productCode, const char* desc);
int  searchProd(TProduct products[], int productCount, const char* productCode);
void showProduct(TProduct products[], int prodCount, const char* prodCode);
void yesOrNo(char* selection);

int main(void)
{
    char     option;
    TProduct products[MAX_PRODUCT];
    int      prodCount = 0;
    Tticket  tickets[MAX_TICKET];
    int      ticketCount = 0;

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
                modProd(products, prodCount);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '4':
                printf("Busqueda de un producto\n");
                char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];
                printf("Introduce el código de producto: ");
                scanf(" %[^\n]", searchProdCode);
                fflush(stdin);
                showProduct(products, prodCount, searchProdCode);
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

    int pos = searchProd(products, *prodCount, newProduct.prodCode);
    printf("(DEBUG) %d\n", pos);

    return EXIT_SUCCESS;
}

void deleteProduct(TProduct products[], int* prodCount)
{
    char searchProdCode[MAX_PRODUCT_CODE];
    printf("Introduce el código de producto: ");
    scanf(" %[^\n]", searchProdCode);

    showProduct(products, *prodCount, searchProdCode);

    char sel[5];
    yesOrNo(sel);

    if (strcmp("si", sel) == 0 || strcmp("s", sel) == 0) {
        int pos = searchProd(products, *prodCount, searchProdCode);
        if (pos == -1)
            printf("Producto no encontrado\n");
        else {
            for (int i = pos; i < *prodCount - 1; i++) {
                products[i] = products[i + 1];
            }
            (*prodCount)--;
        }
    }
    else
        printf("Borrado de producto cancelado\n");
}

void modProd(TProduct products[], int prodCount)
{
    char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];
    printf("Introduce el código de producto: ");
    scanf(" %[^\n]", searchProdCode);

    showProduct(products, prodCount, searchProdCode);

    char sel[5];
    yesOrNo(sel);

    if (strcmp("si", sel) == 0 || strcmp("s", sel) == 0) {
        int pos = searchProd(products, prodCount, searchProdCode);
        printf("(DEBUG) Product position in vector: %d\n", pos);

        if (pos == -1)
            printf("Error: producto no encontrado\n");
        else if (pos > -1) {
            printf("Introduce la descripción del producto: ");
            scanf(" %[^\n]", products[pos].desc);

            printf("Introduce el stock actual: ");
            scanf("%d", &products[pos].stock);

            printf("Introduce el stock minimo: ");
            scanf("%d", &products[pos].minStock);

            printf("Introduce el precio por unidad: ");
            scanf("%f", &products[pos].unitPrice);

            printf("Introduce el descuento del producto: ");
            scanf("%f", &products[pos].disc);

            printf("Producto modificado con exito\n");
        }
    }
    else
        printf("Modificación del producto cancelada\n");
}

void createTicket(TProduct *products, int prodCount, Tticket tickets[], int ticketCount)
{
    TticketLine ticketLines[MAX_TICKET_LINES];
    int ticketLinesCount = 0;

    char sel[5];
    printf("Añadiendo lineas de ticket\n");

    do {
        yesOrNo(sel);

        for (int i = 0; i < MAX_TICKET_LINES; i++) {
            char searchProdCode[MAX_PRODUCT_CODE];
            printf("Introduce el código de producto: ");
            scanf(" %[^\n]", searchProdCode);
            int pos = searchProd(products, prodCount, searchProdCode);



            strcpy(ticketLines[i].prodCode, products[pos].prodCode);
            strcpy(ticketLines[i].desc, products[pos].desc);

        }



    } while (strcmp(sel, "si") == 0 || strcmp(sel,  "s") == 0);
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

int searchProd(TProduct products[], int productCount, const char* productCode)
{
    int i = 0, pos = -1;

    while (pos == -1 && i < productCount) {
        if (strcmp(products[i].prodCode, productCode) == 0)
            pos = i;
        else
            i++;
    }
    return pos;
}

void showProduct(TProduct products[], int prodCount, const char* prodCode)
{
    int pos = searchProd(products, prodCount, prodCode);
    printf("(DEBUG) Product position in vector: %d\n", pos);

    if (pos == -1) {
        printf("Error: El producto que buscas no existe\n");
        return;
    }
    else if (pos > -1) {
        printf("\tCódigo: %s\n", products[pos].prodCode);
        printf("\tDescripción: %s\n", products[pos].desc);
        printf("\tStock: %d\n", products[pos].stock);
        printf("\tStock mínimo: %d\n", products[pos].minStock);
        printf("\tPrecio unitario: %.2f\n", products[pos].unitPrice);
        printf("\tDescuento: %.2f\n", products[pos].disc);
    }
}

void yesOrNo(char* selection)
{
    printf("Confirmar borrado (si-s/no-n): ");
    scanf(" %[^\n]", selection);
}
