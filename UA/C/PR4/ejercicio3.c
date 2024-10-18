/*
            PRÁCTICA 4. EJERCICIO 3.
    Para compilar: cc ejercicio3.c -o ejercicio3
    Para ejecutar: ./ejercicio3
    { cc = compilador }
*/
#include <stdio.h>

float needCap(float consumo, int km) {
	float litros = ((float)km/100) * consumo;
	return litros;
}

int main() {

	float consumo;
	int km;

	printf("Introduce el consumo medio del vehículo en litros a los 100kms: ");
	scanf("%f", &consumo);

	printf("Introduce los kilómetros a recorrer: ");
	scanf("%d", &km);

	printf("Los litros necesarios para recorrer los 450 kms son: %.2f\n", needCap(consumo, km));

	return 0;
}
