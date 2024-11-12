/*
            PRÁCTICA 5. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/

#include <stdio.h>
#include <stdlib.h>

int contarDig(int num)
{
	// Caso base |-> Si el numero es menor que 10, siempre tiene 1 digito
	if (num < 10)
		return 1;
	else 
		return 1 + contarDig(num/10);
	
}

int main()
{
	int numero, digitos;

	printf("Introduce un numero entero: ");
	scanf("%d", &numero);

	printf("Funcion para contar digitos: %d\n", contarDig(numero));
}
