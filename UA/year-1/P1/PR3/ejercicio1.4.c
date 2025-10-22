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

    if (sentido == 'A')
    {
        // Ordenar numeros en sentido ascendente
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
        printf("Valores despues del intercambio en sentido %c: a=%d, b=%d, c=%d\n", sentido, a, b, c);
    } else if (sentido == 'D')
    {
        // Ordenar numeros en sentido descendente
        if (b < a) 
        {
            aux = a;
            a = b;
            b = aux;
        }
        if (c < a) 
        {
            aux = a;
            a = c;
            c = aux;
        }
        if (c < b) 
        {
            aux = b;
            b = c;
            c = aux;
        }
        printf("Valores despues del intercambio en sentido %c: a=%d, b=%d, c=%d\n", sentido, a, b, c);
    } else
        printf("Orden incorrecto\n");
    
    return 0;
}
