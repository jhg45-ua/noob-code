#include <stdio.h>
#include <math.h>

void calculateArea(float lado, float *area, float *perimetro)
{
	*area = pow(lado, 2);
	*perimetro = lado * 4;
}

int main()
{
	float lado, area, perimetro;

	printf("Introduce el tamaño del lado: ");
	scanf("%f", &lado);

	calculateArea(lado, &area, &perimetro);

	printf("* Perimetro: %.2f\n*Area: %.2f\n", perimetro, area);
	
	return 0;
}
