/*
            PRÁCTICA 4. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNumInRange(int min, int max) {
	srand(time(NULL));

	int randNum = min + rand() % (max + 1);
	return randNum;
}

int main() {

	int min, max;

	printf("Introduce el minimo y maximo del rango para generar un numero: ");
	scanf("%d %d", &min, &max);

	printf("El numero generado es: %d\n", randNumInRange(min, max));

	return 0;
}
