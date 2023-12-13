/*
            PRÁCTICA 5. EJERCICIO 1.
    Para compilar: cc ejercicio1.c -o ejercicio1
    Para ejecutar: ./ejercicio1
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>

int menu(int *op);
float CelToFar(float *tempI, float *tempF);
float FarToCel(float *tempI, float *tempF);

int main() {
  int op;
  float tempI, tempF;

  do {
    menu(&op);
    switch (op) {
    case 1:
      CelToFar(&tempI, &tempF);
      printf("El resultado en Farhenheit es: %.2f\n", tempF);
      break;
    case 2:
      FarToCel(&tempI, &tempF);
      printf("El resultado en Celcius es: %.2f\n", tempF);
      break;
    }
  } while (op != 3);

  printf("GoodBye\n");

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
