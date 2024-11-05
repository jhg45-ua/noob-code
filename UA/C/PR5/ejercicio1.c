/*
            PRÁCTICA 5. EJERCICIO 1.
    Para compilar: cc ejercicio1.c -o ejercicio1
    Para ejecutar: ./ejercicio1
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>

void recTri(int n)
{
	if (n <= 0)
		return;

	recTri(n - 1);

	for (int i = 0; i < n; i++)
	{
		printf("*");
	}
	printf("\n");
}

int main()
{
	int altura;
	
	printf("Introdue la altura del triangulo: ");
	scanf("%d", &altura);

	recTri(altura);
}
