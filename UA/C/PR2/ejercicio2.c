/*
           PRÁCTICA 2. EJERCICIO 2.
  Para compilar:  cc ejercicio2.c -o ejercicio2
  Para ejecutar: ./ejercicio2
  { cc = compilador }
*/
#include <stdio.h>

int main() 
{
	float pesoBolsa, monedaRef, pesoMoneda;

	// Se piden los datos
	printf("Introduce el peso de la saca (Kg): ");
	scanf("%f", &pesoBolsa);

	printf("Introduce el valor de las monedas (€): ");
	scanf("%f", &monedaRef);

	printf("Introduce el peso de la moneda (g): ");
	scanf("%f", &pesoMoneda);

	// Calculamos la cantidad de monedas segun el peso de la bolsa y el peso individual de la monedas
	int cantidadMonedas = (pesoBolsa * 1000) / pesoMoneda; // cantidad de monedas
	float valorTotal = cantidadMonedas * monedaRef; //valor total de la bolsa

	printf("La bolsa de %.0f que pesa %f tiene un valor: %.2f€\n", monedaRef, pesoBolsa, valorTotal);
  	return 0;
}
