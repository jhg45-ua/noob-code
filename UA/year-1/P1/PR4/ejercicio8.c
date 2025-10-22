#include <stdio.h>
#include <math.h>

void ec2grado(float a, float b, float c, float *raiz1, float *raiz2)
{
	// Calculamos la discriminante
    	float discriminante = b * b - 4 * a * c;

    	// Calculamos las raices
	*raiz1 = (-b + sqrt(discriminante)) / (2 * a);
    	*raiz2 = (-b - sqrt(discriminante)) / (2 * a);
}


int main() {
    	float a, b, c;
    	float x1, x2;

    	printf("Introduce el coeficiente a, b y c separados por espacios: ");
    	scanf("%f %f %f", &a, &b, &c);

	ec2grado(a, b, c, &x1, &x2);

	printf("Las raices del polinomio y pundos de corte con el eje X son:\n");
    	printf("x1 = %.2f\n", x1);
    	printf("x2 = %.2f\n", x2);
    
	return 0;
}
