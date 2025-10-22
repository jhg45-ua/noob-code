/*
            PRÁCTICA 3. EJERCICIO 1.4b
    Para compilar: cc ejercicio1.4b.c -o ejercicio1.4b
    Para ejecutar: ./ejercicio1.4b
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{

    int a, b, c;
    int aux;
    char sentido;
    
    printf("Introduce el valor de a: ");
    scanf("%d", &a);

    printf("Introduce el valor de b: ");
    scanf("%d", &b);

    printf("Introduce el valor de c: ");
    scanf("%d", &c);

    printf("Ordenar en sentido Ascendente (A) o Descendente (D): ");
    scanf(" %c", &sentido);

    printf("Valores antes del intercambio: a=%d, b=%d, c=%d\n", a, b, c);

    if (sentido == 'A' && b > a || sentido == 'D' && b < a)
    {
        aux = a;
        a = b;
        b = aux;
    } 
    if (sentido == 'A' && c > a || sentido == 'D' && c < a)
    {
        aux = a;
        a = c;
        c = aux;
    } 
    if (sentido == 'A' && c > b || sentido == 'D' && c < b)
    {
        aux = b;
        b = c;
        c = aux;
    } else
        printf("Orden incorrecto\n");

    printf("Valores despues del intercambio en sentido %c: a=%d, b=%d, c=%d\n", sentido, a, b, c);
    
    return 0;
}
