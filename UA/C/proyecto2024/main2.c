#include <stdio.h>
#include <string.h>
#include <time.h>

#define KLINEAS 10

typedef char TLetras[4];
typedef char TDescripcion[31];

typedef struct {
    int dia, mes, anyo;
} TFecha;
typedef struct {
    int horas, minutos;
} THora;

typedef struct {
    TLetras letras; // char letras[4]; // "abc"
    int     numero;
} TCodigo;

typedef struct {
    TCodigo      codigo;
    TDescripcion descripcion; // char descripcion[31];
    int          stock;
    int          stockMinimo;
    float        precioUnidad;
    float        descuento;
} TProducto;
typedef TProducto TProductos[50]; // El tipo vector de productos.

typedef struct {
    TCodigo producto;
    int     vendidas;
} TLineaTicket;

typedef TLineaTicket TLineasTicket[KLINEAS];
typedef struct {
    int           codigo;
    TFecha        fechaVenta;
    THora         horaVenta;
    TLineasTicket lineas;
    int           numLineas;
} TTicket;

typedef TTicket TTickets[100];
typedef struct {
    TProductos productos; // TProducto productos[50];
    int        numProductos;
    TTickets   tickets;
    int        numTickets;
} TTienda;

void imprimirCodigo(TCodigo codigo);
void imprimirProducto(TProducto p);
void imprimirProductos(TProductos productos, int numProductos);
void comprobarStock(TProductos productos, int numProductos);
TCodigo leerCodigo();
int buscarProducto(TProductos productos, int numProductos, TCodigo codigo, TDescripcion descripcion);
THora leerHora();
TFecha leerFecha();
char preguntar();



int main()
{
    // inicializacion estatica del vector para tener
    // datos desde el principio.
    TTienda tienda = {
        // Productos
        {
            {{"A01", 1}, "Manzanas", 100, 10, 0.5, 0.1},
            {{"B02", 2}, "Peras", 50, 5, 0.7, 0.05},
            {{"C03", 3}, "Plátanos", 120, 15, 0.6, 0.08},
            {{"D04", 4}, "Naranjas", 80, 20, 0.8, 0.1},
            {{"E05", 5}, "Melones", 30, 3, 1.5, 0.15},
            {{"F06", 6}, "Sandías", 25, 5, 2.0, 0.2}},
        6, // Número de productos

        // Tickets
        {
            {
                1,              // Código del ticket
                {10, 12, 2024}, // Fecha: 10/12/2024
                {14, 30},       // Hora: 14:30
                {               // Líneas del ticket
                 {{"A01", 1}, 5},
                 {{"B02", 2}, 3},
                 {{"C03", 3}, 10}},
                3 // Número de líneas
            },
            {
                2,              // Código del ticket
                {11, 12, 2024}, // Fecha: 11/12/2024
                {16, 45},       // Hora: 16:45
                {               // Líneas del ticket
                 {{"D04", 4}, 4},
                 {{"E05", 5}, 2},
                 {{"F06", 6}, 1},
                 {{"A01", 1}, 7}},
                4 // Número de líneas
            }},
        2 // Número de tickets
    };

    printf("\n\n");
    // imprime el producto que se encuentra en la posicion 0.
    imprimirProducto(tienda.productos[0]);
    // imprimimos todos los productos.
    for (int i = 0; i < tienda.numProductos; i++) {
        imprimirProducto(tienda.productos[i]);
    }
    printf("IMPRIMIENDO PRODUCTOS CON LA PUTA FUNCION\n");
    imprimirProductos(tienda.productos, tienda.numProductos);

    // Leer un codigo
    // Leer una descripcion
    // He indicar la posicion que ocupa en el vector de producto

    printf("AHORA VAMOS A BUSCAR UN PRODUCTO\n");
    printf("================================\n");
    TCodigo      codigo;
    TDescripcion descripcion;
    int          pos;
    codigo = leerCodigo();
    printf("Descripcion: ");
    scanf(" %[^\n]", descripcion);
    pos = buscarProducto(tienda.productos, tienda.numProductos, codigo, descripcion);
    if (pos == -1) {
        printf("No hemos encontrado el producto\n");
    }
    else {
        printf("Producto encontrado en la posicion %d\n", pos);
    }

    // Leer un producto nuevo!
    printf("AHORA VAMOS A DAR DE ALTA UN PRODUCTO\n");
    TProducto nuevo;
    nuevo.codigo = leerCodigo();
    printf("Descripcion: ");
    scanf(" %[^\n]", nuevo.descripcion);
    pos = buscarProducto(tienda.productos, tienda.numProductos, codigo, descripcion);
    if (pos == -1) {
        // sigo rellenando nuevo con el resto de datos.
        printf("Stock: ");
        scanf("%d", &nuevo.stock);
        printf("Stock minimo: ");
        scanf("%d", &nuevo.stockMinimo);
        printf("Precio: ");
        scanf("%f", &nuevo.precioUnidad);
        printf("Descuento: ");
        scanf("%f", &nuevo.descuento);
        tienda.productos[tienda.numProductos] = nuevo;
        tienda.numProductos++;
        imprimirProductos(tienda.productos, tienda.numProductos);
    }
    else {
        printf("PRODUCTO YA EXISTENTE EN LA POSICION %d\n", pos);
    }

    // AHORA VAMOS A BURRAR UN PRODUCTO.
    printf("Intorduce los datos del producto a borrar\n");
    printf("Introduce el codigo: ");
    codigo = leerCodigo();
    printf("Introduce la descripcion: ");
    scanf(" %[^\n]", descripcion);
    pos = buscarProducto(tienda.productos, tienda.numProductos, codigo, descripcion);
    if (pos == -1) {
        printf("No puedo eliminar lo que no existe\n");
    }
    else {
        for (int i = pos; i < tienda.numProductos - 1; i++) {
            tienda.productos[i] = tienda.productos[i + 1];
        }
        tienda.numProductos--;
    }
    // y añadimos ese producto a los putos productos exsitentes!!
    comprobarStock(tienda.productos, tienda.numProductos);

    // vamos a dar de alta un ticket
    printf("================\n");
    printf("%ld\n", time(NULL));
    printf("%ld\n", time(NULL));
    printf("%ld\n", time(NULL));
    printf("================\n");

    TTicket nuevot;
    char    respuesta;
    nuevot.codigo     = time(NULL);
    nuevot.fechaVenta = leerFecha();
    nuevot.horaVenta  = leerHora();
    do {
        // hay que leer una linea de ticket
        TLineaTicket nueva;

        // hay que meter la linea nueva en el ticket nuevot

        respuesta = preguntar(); // devuelve s o n.
    } while (respuesta == 's');
    tienda.tickets[tienda.numTickets] = nuevot;
    tienda.numTickets++;

    return 0;
}

void imprimirCodigo(TCodigo codigo)
{
    printf("%s - %d", codigo.letras, codigo.numero);
}

void imprimirProducto(TProducto p)
{
    printf("Codigo: ");
    imprimirCodigo(p.codigo);
    printf("\nDescripcion: %s\n", p.descripcion);
    printf("Stock: %d\n", p.stock);
    printf("Stock minimo: %d\n", p.stockMinimo);
    printf("Precio unidad: %.2f\n", p.precioUnidad);
    printf("Descuento: %.2f\n", p.descuento);
}

void imprimirProductos(TProductos productos, int numProductos)
{
    if (numProductos == 0) {
        printf("No hay productos\n");
    }
    else {
        printf("LIstado de productos nazix\n");
        for (int i = 0; i < numProductos; i++) {
            imprimirProducto(productos[i]);
            printf("\n");
        }
    }
}

/*
Comprobar stock. Esta acción recorrerá los productos en stock y listará todos
aquéllos con un stock igual o inferior al stock mínimo para que el usuario pueda
hacer el pedido al proveedor. Para cada producto se mostrará toda su
información. El listado debe verse tabulado.
*/
void comprobarStock(TProductos productos, int numProductos)
{
    if (numProductos == 0) {
        printf("No existen productos en la tienda\n");
    }
    else {
        printf("Productos que estan por debajo del stock minimo\n");
        for (int i = 0; i < numProductos; i++) {
            if (productos[i].stock < productos[i].stockMinimo) {
                imprimirProducto(productos[i]);
                printf("\n");
            }
        }
    }
}

TCodigo leerCodigo()
{
    TCodigo codigo;
    printf("Introduce 3 letras: ");
    scanf(" %s", codigo.letras);
    printf("Introduce un numero: ");
    scanf(" %d", &codigo.numero);
    return codigo;
}

int buscarProducto(TProductos productos, int numProductos, TCodigo codigo, TDescripcion descripcion)
{
    int i, pos;

    i   = 0;
    pos = -1;
    while (pos == -1 && i < numProductos) {
        if (strcmp(descripcion, productos[i].descripcion) == 0 && codigo.numero == productos[i].codigo.numero && strcmp(codigo.letras, productos[i].codigo.letras) == 0) { // si lo encuentro cambio el valor de pos y paro el bucle.
            pos = i;
        }
        else {
            i++;
        }
    }
    return pos;
}

THora leerHora()
{
    THora hora;
    return hora;
}

TFecha leerFecha()
{
    TFecha fecha;
    return fecha;
}

char preguntar()
{
    char respuesta;
    return respuesta;
}
