/*
            PRÁCTICA 3. EJERCICIO 1.4
    Para compilar: cc ejercicio1.4.c -o ejercicio1.4
    Para ejecutar: ./ejercicio1.4
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{

    int a, b, c;
    int aux;
    
    printf("Introduce el valor de a: ");
    scanf("%d", &a);

    printf("Introduce el valor de b: ");
    scanf("%d", &b);

    printf("Introduce el valor de c: ");
    scanf("%d", &c);

    printf("Valores antes del intercambio: a=%d, b=%d, c=%d\n", a, b, c);

    // Ordenar numeros
    if (b > a) 
    {
        aux = a;
        a = b;
        b = aux;
    }
    if (c > a) 
    {
        aux = a;
        a = c;
        c = aux;
    }
    if (c > b) 
    {
        aux = b;
        b = c;
        c = aux;
    }

    printf("Valores despues del intercambio: a=%d, b=%d, c=%d\n", a, b, c);

    return 0;
}
