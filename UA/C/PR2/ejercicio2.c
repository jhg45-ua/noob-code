/*
           PRÁCTICA 2. EJERCICIO 2.
  Para compilar:  cc ejercicio2.c -o ejercicio2
  Para ejecutar: ./ejercicio2
  { cc = compilador }
*/
#include <stdio.h>

int main() {
  float litros, consumo, kms;

  printf("Introduce los litros de combustible que hay en el depósito: ");
  scanf("%f", &litros);

  printf("Introduce el consumo medio de litros a los 100 kms: ");
  scanf("%f", &consumo);

  // Se calcula la autonomía del vehículo en kms
  kms = (litros * 100) / consumo;

  printf("La autonomía de tu vehículo son %.2f kms\n", kms);

  return 0;
}
