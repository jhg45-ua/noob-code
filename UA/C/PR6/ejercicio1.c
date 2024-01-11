#include <stdio.h>
#include <stdlib.h>

// void divisores(int n);
//
// int main() {
//
//   int num;
//
//   printf("Introduce un numero entero positivo: ");
//   scanf("%d", &num);
//
//   divisores(num);
//
//   return 0;
// }
//
// void divisores(int num) {
//
//   int nd = 1;
//
//   printf("Divisores: 1");
//   for (int i = 2; i <= num; i++) {
//     nd = (nd + 1);
//     if (num % i == 0) {
//       printf(", %d", i);
//     }
//   }
//   printf("\nNumero de divisores: %d\n", nd / 2);
// }

void encontrarDivisores(int *numero, int divisores, int *counter);

int main() {

  int numero, counter = 0;

  printf("Introduce un numero positivo: ");
  scanf("%d", &numero);

  if (numero < 1) {
    printf("Por favor introduce un numero positio");
    return 1;
  }

  printf("Divisores de %d: ", numero);
  encontrarDivisores(&numero, 1, &counter);
  printf("\n");

  printf("Total: %d\n", counter);

  return 0;
}

void encontrarDivisores(int *numero, int divisor, int *counter) {

  if (divisor > *numero)
    return;

  if (*numero % divisor == 0) {
    printf("%d ", divisor);
    (*counter)++;
  }

  encontrarDivisores(numero, divisor + 1, counter);
}
