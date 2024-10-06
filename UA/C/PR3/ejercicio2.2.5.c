#include <stdio.h>
#include <stdlib.h>

int main()
{
	int input, cifra;
	int totalCifras = 0, totalPares = 0, totalImpares = 0;

	// Solicita el numero
	printf("Introduce un número entero: ");
	scanf("%d", &input);

	if (input < 0)
		input = -input;

	if (input == 0)
	{
		totalCifras = 1;
		totalPares = 1;
	}


	while (input > 0) 
	{
		cifra = input % 10;
		totalCifras++;

		if (cifra % 2 == 0)
			totalPares++;
		else
			totalImpares++;
		input /= 10;
	}

	printf("Total de cifras: %d\n", totalCifras);
	printf("Total de cifras pares: %d\n", totalPares);
	printf("Total de cifras impares: %d\n", totalImpares);

	return  EXIT_SUCCESS;
}

/*
 * Para descomponer en sus digitos un numero,
 * vas haciendo el modulo entre 10 para obtener el ultimo numero y
 * luego dividir entre 10 para quitar el ultimo digito. Repetirlo
 * hasta que el numero de inicio sea 0
 *
 */
