/*
            PRÁCTICA 4. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNumInRange(int min, int max) { return min + rand() % (max - min + 1); }

int main() {
	int min, max, nNum;

	srand(time(NULL)); // La semilla solo hace falta iniciarla una vez

	printf("Introduce el minimo y maximo del rango para generar un numero: ");
	scanf("%d %d", &min, &max);

	printf("Cuantos numeros pseudoaleatorios quieres: ");
	scanf("%d", &nNum);

	for (int i = 1; i <= nNum; i++)
	{
		printf("El numero generado es: %d\n", randNumInRange(min, max));
	}

	return 0;
}
