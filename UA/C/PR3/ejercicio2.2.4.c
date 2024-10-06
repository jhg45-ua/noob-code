#include <stdio.h>
#include <stdlib.h>

int main()
{
	float input, sumaTotal = 0, contNum = 0;

	do 
	{
		printf("Introduce un número positivo (0 - para terminar): ");
		scanf("%f", &input);

		sumaTotal += input;
		printf("Debug sumTotal: %.2f\n", sumaTotal);
		if (input > 0)
			contNum++;
	} while (!(input == 0));

	printf("Total de números: %.2f\n", contNum);

	float mediaArit = sumaTotal/contNum;
	printf("Media aritmética calculada: %.2f\n", mediaArit);
	

	return EXIT_SUCCESS;
}
