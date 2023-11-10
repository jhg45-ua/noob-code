#include <stdio.h>
#include <stdlib.h>

void divisores(int n);

int main() {

  int num;

  printf("Introduce un numero entero positivo: ");
  scanf("%d", &num);

  divisores(num);

  return 0;
}

void divisores(int num) {

  int nd = 1;

  printf("Divisores: 1");
  for (int i = 2; i <= num; i++) {
    nd = (nd + 1);
    if (num % i == 0) {
      printf(", %d", i);
    }
  }
  printf("\nNumero de divisores: %d\n", nd / 2);
}
