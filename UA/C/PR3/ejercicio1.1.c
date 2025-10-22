/*
            PRÁCTICA 3. EJERCICIO 1.1
  Para compilar:  cc ejercicio1.1.c -o ejercicio1.1
  Para ejecutar: ./ejercicio1.1
  { cc = compilador }
*/
#include <stdio.h>

int main()
{
    int numero1, numero2;

    printf("Introduce un número: ");
    scanf("%d", &numero1);

    printf("Escribe otro número entero: ");
    scanf("%d", &numero2);

    if (numero1 > numero2)
        printf("El numero %d es mayor que el numero %d", numero1, numero2);
    else
        printf("El numero %d es mayor que el numero %d", numero2, numero1);

    if (numero1 == numero2)
        printf("El numero %d y el numero %d son iguales", numero1, numero2);
        
    return 0;
}