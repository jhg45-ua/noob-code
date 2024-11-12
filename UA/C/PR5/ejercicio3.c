/*
            PRÁCTICA 5. EJERCICIO 3.
    Para compilar: cc ejercicio3.c -o ejercicio3
    Para ejecutar: ./ejercicio3
    { cc = compilador }
*/

#include <stdio.h>
#include <stdlib.h> // para utilizar rand() y generar los números pseudoaleatorios

int potRec(int base, int exponente)
{
	// Caso base |-> si el exponente es 1 devuelve la base 
	if (exponente == 1)
		return base;
	else
		return base * potRec(base, exponente - 1);
}

int main()
{
	int n, m;

	printf("Introduce dos numeros enteros n y m: ");
	scanf("%d %d", &n, &m);

	printf("El resultado es: %d\n", potRec(n, m));

	return 0;
}
