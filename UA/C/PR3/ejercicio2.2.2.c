/*
            PRÁCTICA 3. EJERCICIO 2.2.2
    Para compilar: cc ejercicio2.2.2.c -o ejercicio2.2.2
    Para ejecutar: ./ejercicio2.2.2
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 1
#define MAX 100

int main()
{
	// Para numeros aleatiorios positivos -> en el rango [a, A] n[a, A] = a + rand()%(A+1)
	int numeroMisterioso, input, counter = 0;

	printf("Adivina el número oculto en el menor numero de intentos posibles\n");

	srand(time(NULL));
	numeroMisterioso = MIN + rand() % (MAX + 1);
	//printf("Debug numeroMisterioso: %d\n", numeroMisterioso);

	do
	{
		printf("Introduce un número: ");
		scanf("%d", &input);

		if (input < numeroMisterioso)
			printf("El número oculto es MAYOR\n");
		else if (input > numeroMisterioso) 
			printf("El número oculto es MENOR\n");

		counter++;
	} while (input != numeroMisterioso);

	printf("ENORABUENA!! Has acertado el número oculto en %d intentos\n", counter);

	return EXIT_SUCCESS;
}
