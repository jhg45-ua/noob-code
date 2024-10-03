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
#define MAX 5

int main()
{
	int generatedNums = 0, counter = 0;
	int num1, num2, num3;

	printf("Los números distintos son: ");

	srand(time(NULL));
	do 
	{
		int randNum = MIN + rand()% (MAX + 1);
		generatedNums++;

		if (counter == 0)
		{
			printf("%d ", randNum);
			num1 = randNum;
			counter++;
		} else if (counter == 1)
		{
			if (randNum != num1)
			{
				printf("%d ", randNum);
				num2 = randNum;
				counter++;
			}
		} else 
		{
			if (randNum != num1 && randNum != num2)
			{
				printf("%d ", randNum);
				num3 = randNum;
				counter++;
			}
		}
	} while (counter < 3);
	printf("\n");

	printf("Números totales generados: %d\n", generatedNums);

	return EXIT_SUCCESS;
}
