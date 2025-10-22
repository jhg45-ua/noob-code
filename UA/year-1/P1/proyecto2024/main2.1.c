#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Constantes
#define MAX_PRODUCT_CODE 5 // 3 letters + 1 num + \0
#define MAX_DESCRIPTION 30
#define MAX_TICKET_LINES 10
#define MAX_TICKET 100
#define MAX_PRODUCT 50
#define SLEEP_TIME 1

typedef struct {
    int day, month, year;
} TDate;
typedef struct {
    int hour, minutes;
} THour;

typedef struct {
    char prodCode[MAX_PRODUCT_CODE], desc[MAX_DESCRIPTION];
    int stock, minStock;
    float unitPrice, discount; // Discount percentage (5% -> 5.0)
} TProducto;
typedef TProducto TProductos[MAX_PRODUCT];

typedef struct {
    char prodCode[MAX_PRODUCT_CODE], sellprodDesc[MAX_DESCRIPTION];
    int vendidas;
} TLineaTicket;
typedef TLineaTicket TLineasTicket[MAX_TICKET_LINES];

typedef struct {
    int ticketCod;
    TDate sellDate;
    THour sellHour;
    TLineasTicket lines;
    int lineNum;
} TTicket;
typedef TTicket TTickets[100];

typedef struct {
    TProductos productos; // TProducto productos[50];
    int productNum;
    TTickets tickets; // TTicket TTickets[100];
    int ticketNum;
    int nextId;
} TStore;

// Prototipos de funciones
void mainMenu();
void printProd(TProducto p);
void printProds(TProductos products, int prodNum);
void checkStock(TProductos products, int prodNum);
int searchProdPos(TProductos products, int prodNum, const char *prodCode, const char *prodDesc);
THour readHour();
TDate readDate();
void altaProd(TProductos products, int *prodNum);
char preguntar();
void bajaProd(TProductos products, int *prodNum);
bool searhProd(TProductos products, int prodNum);
void altaTicket(TProductos products, int prodNum, TTickets tickets, int *ticketNum, int *nextId);
void modificarBuscar(TTickets tickets, int *ticketsNum);


int main(void)
{
    // inicializacion estatica del vector para tener
    // datos desde el principio.
    TStore tienda = {
        // Productos
        {
            {"A001", "Manzanas", 100, 10, 0.5, 0.1},
            {"B002", "Peras", 50, 5, 0.7, 0.05},
            {"C003", "Plátanos", 120, 15, 0.6, 0.08},
            {"D004", "Naranjas", 80, 20, 0.8, 0.1},
            {"E005", "Melones", 30, 3, 1.5, 0.15},
            {"F006", "Sandías", 25, 5, 2.0, 0.2}},
        6, // Número de productos

        // Tickets
        {
            {
                1,              // Código del ticket
                {10, 12, 2024}, // Fecha: 10/12/2024
                {14, 30},       // Hora: 14:30
                {               // Líneas del ticket
                 {"A001", 5},
                 {"B002", 3},
                 {"C003", 10}},
                3 // Número de líneas
            },
            {
                2,              // Código del ticket
                {11, 12, 2024}, // Fecha: 11/12/2024
                {16, 45},       // Hora: 16:45
                {               // Líneas del ticket
                 {"D004", 4},
                 {"E005", 2},
                 {"F006", 1},
                 {"A001", 7}},
                4 // Número de líneas
            }},
        2 // Número de tickets
    };

    char     option;
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
                altaProd(tienda.productos, &tienda.productNum);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '2':
                printf("Baja de un producto\n");
                bajaProd(tienda.productos, &tienda.productNum);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '3':
                printf("Modificación de un producto (WIP)\n");
                //modProd(tienda.productos, prodCount);
                sleep(SLEEP_TIME);
                system("clear");
                break;
            case '4':
                printf("Busqueda de un producto\n");
                char searchProdCode[MAX_PRODUCT_CODE];
                printf("Introduce el código de producto: ");
                scanf(" %[^\n]", searchProdCode);
                fflush(stdin);
                //showProduct(tienda.productos, tienda.productNum, searchProdCode);
                printf("Presione cualquier tecla para continuar");
                getchar();
                break;
            case '5':
                printf("Crear un nuevo ticket (WIP)\n");
                altaTicket(tienda.productos, tienda.productNum, tienda.tickets, &tienda.ticketNum, &tienda.nextId);
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
                checkStock(tienda.productos, tienda.productNum);
                printf("Presione cualquier tecla para continuar");
                getchar();
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

void printProd(TProducto p)
{
    printf("Codigo: %s", p.prodCode);
    printf("\nDescripcion: %s\n", p.desc);
    printf("Stock: %d\n", p.stock);
    printf("Stock minimo: %d\n", p.minStock);
    printf("Precio unidad: %.2f\n", p.unitPrice);
    printf("Descuento: %.2f\n", p.discount);
}

void printProds(TProductos products, int prodNum)
{
    if (prodNum == 0)
        printf("No hay productos\n");
    else {
        printf("Listado de productos completo\n");
        for (int i = 0; i < prodNum; i++) {
            printProd(products[i]);
            printf("\n");
        }
    }
}

void checkStock(TProductos products, int prodNum)
{
    if (prodNum == 0)
        printf("No existen productos en la tienda\n");
    else {
        printf("Productos por debajo del stockt minimo\n");
        for (int i = 0; i < prodNum; i++) {
            if (products[i].stock < products[i].minStock) {
                printProd(products[i]);
                printf("\n");
            }
        }
    }
}

int searchProdPos(TProductos products, int prodNum, const char *prodCode, const char *prodDesc)
{
    int i = 0, pos = -1;

    while (pos == -1 && i < prodNum) {
        if (strcmp(prodDesc, products[i].desc) == 0 &&
            strcmp(prodCode, products[i].prodCode) == 0)
            pos = i;
        else
            i++;
    }
    return pos;
}

THour readHour()
{
    THour hour;
    printf("Horas: ");
    scanf("%d", &hour.hour);
    printf("Minutos: ");
    scanf("%d", &hour.minutes);
    return hour;
}

TDate readDate()
{
    TDate date;
    printf("Introduce el dia, mes y año separado por espacios: ");
    scanf("%d %d %d", &date.day, &date.month, &date.year);
    return date;
}

void altaProd(TProductos products, int *prodNum)
{
    printf("AHORA VAMOS A DAR DE ALTA UN PRODUCTO\n");

    TProducto newProduct;
    int pos;

    printf("Código de producto (Ej: ABC1): ");
    scanf(" %[^\n]", newProduct.prodCode);
    printf("Descripción: ");
    scanf(" %[^\n]", newProduct.desc);

    pos = searchProdPos(products, *prodNum, newProduct.prodCode, newProduct.desc);

    if (pos == -1) {
        printf("Introduce el stock actual: ");
        scanf("%d", &newProduct.stock);
        printf("Introduce el stock minimo: ");
        scanf("%d", &newProduct.minStock);
        printf("Introduce el precio por unidad: ");
        scanf("%f", &newProduct.unitPrice);
        printf("Introduce el descuento del producto: ");
        scanf("%f", &newProduct.discount);
        products[*prodNum] = newProduct;
        (*prodNum)++;
    } else
        printf("Producto duplicado\n");
}

char preguntar()
{
    char respuesta;
    do{
        printf("Quieres introducir otra linea(s/n)?: ");
        scanf(" %c", &respuesta);
    }while(respuesta != 's' && respuesta != 'n');
    return respuesta;
}

void bajaProd(TProductos products, int *prodNum)
{
    int pos;
    char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];

    printf("Intorduce los datos del producto a borrar\n");
    printf("Código de producto (Ej: ABC1): ");
    scanf(" %[^\n]", searchProdCode);
    printf("Descripción: ");
    scanf(" %[^\n]", searchProdDesc);

    pos = searchProdPos(products, *prodNum, searchProdCode, searchProdDesc);

    if (pos > -1) {
        for (int i = pos; i < *prodNum; i++) {
            products[i] = products[i+1];
        }
        (*prodNum)--;
    }
}

bool searhProd(TProductos products, int prodNum)
{
    printf("AHORA VAMOS A BUSCAR UN PRODUCTO\n");
    printf("================================\n");

    int pos;
    char searchProdCode[MAX_PRODUCT_CODE], searchProdDesc[MAX_DESCRIPTION];

    printf("Código de producto (Ej: ABC1): ");
    scanf(" %[^\n]", searchProdCode);
    printf("Descripción: ");
    scanf(" %[^\n]", searchProdDesc);

    pos = searchProdPos(products, prodNum, searchProdCode, searchProdDesc);
    if (pos == -1) {
        printf("No hemos encontrado el producto\n");
        return false;
    } else {
        printf("Producto encontrado en la posición %d\n", pos);
        return true;
    }
}

void altaTicket(TProductos products, int prodNum, TTickets tickets, int *ticketNum, int *nextId)
{
    TTicket newTicket;
    char respuesta;


    if (*ticketNum == MAX_TICKET)
        printf("Maximo de tickets alcanzado\n");
    else {
        printf("Introduce los datos del nuevo ticket\n");
        newTicket.ticketCod = *nextId;
        (*nextId)++;
        printf("Introduce la fecha de venta: \n");
        newTicket.sellDate = readDate();
        printf("Introduce la hora de venta: \n");
        newTicket.sellHour = readHour();

        newTicket.lineNum = 0;
        do {
            TLineaTicket newTicketLine;

            printf("Introduce el codigo del producto: ");
            scanf(" %[^\n]", newTicketLine.prodCode);
            printf("Introduce la descripcion del producto: ");
            scanf(" %[^\n]", newTicketLine.sellprodDesc);

            if (searhProd(products, prodNum)) {
                printf("Unidades a comprar: ");
                scanf("%d", &newTicketLine.vendidas);
                newTicket.lines[newTicket.lineNum] = newTicketLine;
                newTicket.lineNum++;
            } else
                printf("El producto que quieres añadir no se encuentra");

            if (newTicket.lineNum < MAX_TICKET_LINES)
                respuesta = preguntar();
        } while (respuesta == 's' && newTicket.lineNum < MAX_TICKET_LINES);

        tickets[*ticketNum] = newTicket;
        (*ticketNum)++;
    }
}

void modificarBuscar(TTickets tickets, int *ticketsNum)
{
    int id, idTicket, posTicket;
    char opcion;

    if (ticketsNum == 0)
        printf("No hay ningun ticket dado de alta\n");
    else {
        printf("Tickets disponibles\n");
        printf("===================\n");
        for(int i = 0; i < *ticketsNum; i++){
            printf("id: %d, fecha: %02d/%02d%04d, hora: %02d:%02d\n",
                   tickets[i].ticketCod, tickets[i].sellDate.day, tickets[i].sellDate.month, tickets[i].sellDate.year,
                   tickets[i].sellHour.hour, tickets[i].sellHour.hour);
        }

        do {
            printf("M- menu principal\n");
            printf("E- Eliminar ticket\n");
            printf("Opcion: ");
            scanf(" %c", &opcion);
            switch(opcion) {
                case 'M':
                    // me salgo de esta funcion
                    break;
                case 'E':
                    printf("Introduce el id de ticket a eliminar: ");
                    scanf("%d", &idTicket); // el idTicket no es la posicion, hay que buscar el ticket con ese id.
                    posTicket = -1;
                    for(int i = 0; i < *ticketsNum && posTicket == -1; i++){
                        if(tickets[i].ticketCod == idTicket){
                            posTicket = i; // posTicket ya no vale -1 y se parara el bucle :)
                        }
                    }

                    if (posTicket > -1) {
                        for (int i = posTicket; i < *ticketsNum - 1; i++) {
                            tickets[i] = tickets[i + 1];
                        }
                        (*ticketsNum)--;
                        printf("Ticket eliminado con exito\n");
                    }
                    break;
            }
        } while (opcion != 'M');
    }
}
