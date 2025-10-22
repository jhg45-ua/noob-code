#include <stdio.h>

void swap2(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int main()
{
	int a, b;

	printf("Introduce dos numeros enteros: ");
	scanf("%d %d", &a, &b);

	printf("Numeros antes del intercambio: a=%d y b=%d\n", a, b);

	swap2(&a, &b);

	printf("Numeros despues del intercambio: a=%d y b=%d\n", a, b);
}
