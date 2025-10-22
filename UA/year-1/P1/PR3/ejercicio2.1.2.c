/*
            PRÁCTICA 3. EJERCICIO 2.1.2
    Para compilar: cc ejercicio2.1.2.c -o ejercicio2.1.2
    Para ejecutar: ./ejercicio2.2
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int numero, divisores;

    printf("Introduce un numero entero: ");
    scanf("%d", &numero);

    printf("Divisores del numero %d: ", numero);
    for (int i = 1; i<=numero; i++)
    {
        if (numero%i == 0)
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}
