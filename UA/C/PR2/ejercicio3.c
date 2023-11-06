/*
            PRÁCTICA 2. EJERCICIO 3.
  Para compilar:  cc ejercicio3.c -o ejercicio3
  Para ejecutar: ./ejercicio3
  { cc = compilador }
*/
#include <stdio.h>
const int LITROS = 5;
const float PI = 3.141593;

int main() {
  float alto, radio, volumen; // para guardar la info del tamaño del vaso
  float aguaSobrante;         // para guardar el agua sobrante
  int nVasos;                 // guardará el número de vasos

  printf("Introduce el alto del vaso en cms: ");
  scanf("%f", &alto);

  printf("Introduce el radio de la base del vaso en cms: ");
  scanf("%f", &radio);

  // Se calcula el volumen del vaso en cm3
  volumen = PI * radio * radio * alto; // en cm3

  // Se calcula el número de vasos enteros que se pueden llenar
  nVasos = LITROS * 1000 / volumen;
  printf("El total de vasos que se pueden llenar es %d\n", nVasos);

  // Se calcula el agua sobrante. Se divide nVasos * volumen por 1000 para
  // convertir el resultado a litros
  aguaSobrante = LITROS - nVasos * volumen / 1000;

  printf("Sobran %f litros de agua\n", aguaSobrante);

  return 0;
}
