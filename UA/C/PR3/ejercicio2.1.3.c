/*
            PRÁCTICA 3. EJERCICIO 2.1.3
    Para compilar: cc ejercicio2.1.3.c -o ejercicio2.1.3
    Para ejecutar: ./ejercicio2.1.3
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int numSoli;
    
    printf("Introduce un numero entero: ");
    scanf("%d", &numSoli);

    if (numSoli < 0)
    {
        printf("El numero solicitado tiene que ser positvo\n");
        return 1;
    }

    printf("Cuanta atras desde %d hasta 0: ", numSoli);

    for (int i = numSoli; i>=0; i--)
    {
        printf("%d", i);
        if (i > 0)
            printf(", ");
    }
    printf("\n");

    return 0;
}
