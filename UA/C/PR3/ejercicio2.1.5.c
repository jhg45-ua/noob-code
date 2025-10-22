#/*
            PRÁCTICA 3. EJERCICIO 2.1.5
    Para compilar: cc ejercicio2.1.5.c -o ejercicio2.1.5
    Para ejecutar: ./ejercicio2.1.5
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int input;

	do
	{
		printf("Introduce un numero par: ");
		scanf("%d", &input);
	} while (!(input%2==0));

	for (int i = 1; i <= input; i += 2)
	{
		for (int j = i; j >= 1; j -= 2)
		{
			printf("%d ", j);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
