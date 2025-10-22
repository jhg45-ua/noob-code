/*
            PRÁCTICA 3. EJERCICIO 2.2.1
    Para compilar: cc ejercicio2.2.1.c -o ejercicio2.2.1
    Para ejecutar: ./ejercicio2.2.1
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int input, cuadrados = 1;

	printf("Introduce un numero entre 50 y 100: ");
	scanf("%d", &input);


	if (input < 50 || input > 100)
	{
		fprintf(stderr, "ERROR: El numero introducido (%d) no esta entre 50 y 100\n", input);
	} else
	{
		printf("Cuadrados perfectos menores que %d: \n", input);
		for (int i = 1; cuadrados < input; i++)
		{
			printf("%d (%d * %d)", cuadrados, i, i);
			cuadrados = i * i;
			if (cuadrados < input)
				printf(", ");
		}
	}
	printf("\n");

	return EXIT_SUCCESS;
}
