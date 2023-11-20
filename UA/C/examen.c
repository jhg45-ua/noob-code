#include <stdio.h>
#include <stdlib.h>

// Prototipos de funciones
void pedirNumeros(int *a, int *b);
void calcularMCDymcm(int a, int b);
void mostrarSolucion(int *a, int *b, int *mcd, int *mcm, int *numerosProbados);

int main() {
  int A, B;

  do {
    // Pide al usuario los valores de A y B
    pedirNumeros(&A, &B);

    // Verifica si A es cero para finalizar el programa
    if (A == 0) {
      printf("Programa finalizado.\n");
      break;
    }

    // Calcula el MCD y mcm
    calcularMCDymcm(abs(A), abs(B));

  } while (1);

  return 0;
}

// Módulo para pedir los números A y B al usuario
void pedirNumeros(int *a, int *b) {
  int countZeros = 0;

  printf("Introduce el valor de A: ");
  scanf("%d", a);

  // Comprueba si A es cero para no pedir B
  if (*a != 0) {
    printf("Introduce el valor de B: ");
    scanf("%d", b);

    // Verifica que B no sea cero y maneja la situación de 3 ceros consecutivos
    while (*b == 0) {
      countZeros++;
      if (countZeros == 3) {
        *b = 1;
        break;
      }

      printf("El valor de B no puede ser cero. Introduce un valor válido para "
             "B: ");
      scanf("%d", b);
    }
  }
}

// Módulo para calcular el MCD y mcm e imprimir los valores probados
void calcularMCDymcm(int a, int b) {
  int mcd, mcm, totalProbados;
  int numerosProbadosMCD = 0, numerosProbadosMCM = 0;

  // Calcula el MCD
  printf("Buscando MCD: ");
  for (mcd = (a < b) ? a : b; mcd >= 1; --mcd) {
    numerosProbadosMCD++;
    printf("%d, ", mcd);

    if (a % mcd == 0 && b % mcd == 0) {
      break;
    }
  }
  printf("\n");

  // Calcula el mcm
  printf("Prueba 10 números para el mcm: ");
  for (mcm = (a > b) ? a : b;; mcm += (a > b) ? a : b) {
    numerosProbadosMCM++;
    printf("%d, ", mcm);

    if (mcm % a == 0 && mcm % b == 0) {
      break;
    }
  }
  printf("\n");

  totalProbados = numerosProbadosMCD + numerosProbadosMCM;

  // Muestra la solución
  mostrarSolucion(&a, &b, &mcd, &mcm, &totalProbados);
}

// Módulo para mostrar la solución y la cantidad de números probados
void mostrarSolucion(int *a, int *b, int *mcd, int *mcm, int *numerosProbados) {
  printf("De los datos %d y %d, el MCD es %d y el mcm es %d.\n", *a, *b, *mcd,
         *mcm);
  printf("En el proceso de cálculo hemos probado con %d números.\n",
         *numerosProbados);
}
