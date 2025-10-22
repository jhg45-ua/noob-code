/*
            PRÁCTICA 3. EJERCICIO 2.1.1
    Para compilar: cc ejercicio2.1.1.c -o ejercicio2.1.1
    Para ejecutar: ./ejercicio2.1.1
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int numeroTabla;

    printf("Introduce un numero entero: ");
    scanf("%d", &numeroTabla);

    for (int i = 0; i <= 10; i++)
    {
        int resultadoTabla = numeroTabla * i;
        printf("%d x %d = %d\n", numeroTabla, i, resultadoTabla);
    }

    return 0;
}
