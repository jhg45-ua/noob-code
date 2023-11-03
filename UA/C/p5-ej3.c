#include <stdio.h>
#include <stdlib.h>

int menu(int *op);
float CelToFar(float *tempI, float *tempF);
float FarToCel(float *tempI, float *tempF);

int main() {
  int op;
  float tempI, tempF;

  menu(&op);

  switch (op) {
  case 1:
    printf("Caso 1\n");
    CelToFar(&tempI, &tempF);
    printf("El resultado en Farhenheit es: %.2f\n", tempF);
    break;
  case 2:
    printf("Caso 2\n");
    FarToCel(&tempI, &tempF);
    printf("El resultado en Celsius : %.2f\n", tempF);
    break;
  case 3:
    printf("Bye\n");
    break;
  }

  return 0;
}

int menu(int *op) {
  printf("1. Convertir de Celsius a Farhenheit\n");
  printf("2. Convertir de Farhenheit a Celcius\n");
  printf("3. Salir\n");
  printf("Opcion: ");
  scanf(" %d", op);

  return *op;
}

float CelToFar(float *tempI, float *tempF) {

  printf("Introduce la temperatura en Celsius: ");
  scanf(" %f", tempI);

  *tempF = (*tempI * 1.8) + 32;

  return *tempF;
}

float FarToCel(float *tempI, float *tempF) {

  printf("Introduce la temperatura en Farhenheit: ");
  scanf(" %f", tempI);

  *tempF = (*tempI - 32) / 1.8;

  return *tempF;
}
