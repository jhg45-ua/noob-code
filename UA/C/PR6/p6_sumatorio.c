#include <stdio.h>
#include <stdlib.h>

int sumatorio(int A);

int main() {
  int n;

  printf("Introduce un numero para calcular el sumatorio: ");
  scanf("%d", &n);

  printf("Sumatorio: %d\n", sumatorio(n));

  return 0;
}

int sumatorio(int A) {

  printf("Calculando el sumatorio de %d\n", A);

  if (A == 0) {
    return 0;
  } else {
    return A + sumatorio(A - 1);
  }
}
