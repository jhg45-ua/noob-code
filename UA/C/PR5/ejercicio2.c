/*
            PRÁCTICA 5. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/

#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

int main()
{
	int numero, digitos;

	printf("Introduce un numero entero: ");
	scanf("%d", &numero);

	while (numero >= 0)
	{
		numero %= 10;
		digitos++;
		numero /= 10;
	}

	printf("Digitos del numero: %d\n", digitos);
}
