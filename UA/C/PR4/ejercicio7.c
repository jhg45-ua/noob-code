#include <stdio.h>

void minAndMax(float num1, float num2, float num3, float *numMayor, float *numMenor)
{
	if (num1 >= num2 && num1 >= num3)
		*numMayor = num1;
	else if (num2 >= num1 && num2 >= num3)
		*numMayor = num2;
	else
		*numMayor = num3;
	
	if (num1 <= num2 && num2 <= num3)
		*numMenor = num1;
	else if (num2 <= num1 && num2 <= num3)
		*numMenor = num2;
	else
		*numMenor = num3;
}

int main()
{
	float num1, num2, num3, numMenor, numMayor;

	printf("Introduce tres numeros flotantes separados por espacios: ");
	scanf("%f %f %f", &num1, &num2, &num3);

	minAndMax(num1, num2, num3, &numMayor, &numMenor);	

	printf("El menor de los tres es %.2f y el mayor es %.2f\n", numMenor, numMayor);


	return 0;
}
