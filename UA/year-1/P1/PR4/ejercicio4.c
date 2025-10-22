/*
            PRÁCTICA 4. EJERCICIO 4.
    Para compilar: cc ejercicio4.c -o ejercicio4 -lm
    Para ejecutar: ./ejercicio4
    { cc = compilador }
*/
#include <stdio.h>
#include <math.h>

float calcularCir(float radio) {
	float longitud = 2 * M_PI * radio;
	return longitud;
}

float calcularArea(float radio) {
	float area = M_PI * pow(radio, 2);
	return area;
}

int main() {

	float radio;

	printf("Introduce el radio: ");
	scanf("%f", &radio);

	printf("* Longitud de la circunferencia: %.2f\n", calcularCir(radio));
	printf("* Área: %.2f\n", calcularArea(radio));

	return 0;
}
