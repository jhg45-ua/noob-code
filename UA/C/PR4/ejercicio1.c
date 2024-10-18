/*
                PRÁCTICA 4. EJERCICIO 1.
    Para poder compilar hay que tener los ficheros gfx.h y gfx.c en la misma
    carpeta que ejercicio1.c Para compilar: cc ejercicio1.c -o ejercicio1
    Para ejecutar: ./ejercicio1

    { cc = compilador }
*/
#include <stdio.h>

void convKmHtoMs(float *kmh, float *ms) { *ms = *kmh / 3.6; }

int main() {
	float velokms=0.0, veloms=0.0;

	printf("Introduce la velocidad (Km/H): ");
	scanf("%f", &velokms);

	convKmHtoMs(&velokms, &veloms);

	printf("La velocidad en m/s: %.2f\n", veloms);

	return 0;
}
