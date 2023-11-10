#include <stdio.h>
#include <stdlib.h>

void hanoi(int N, char PosteInicial, char PosteApoyo, char PosteDestino);

int main() {
  int Ndiscos;

  printf("Introduce el numero de discos: ");
  scanf("%d", &Ndiscos);

  hanoi(Ndiscos, 'a', 'b', 'c');

  return 0;
}

void hanoi(int N, char PosteInicial, char PosteApoyo, char PosteDestino) {

  if (N == 1) {
    printf("mueve 1 disco del poste %c hasta el poste %c\n", PosteInicial,
           PosteDestino);
  } else {

    hanoi(N - 1, PosteInicial, PosteDestino, PosteApoyo);
    hanoi(1, PosteInicial, PosteApoyo, PosteDestino);
    hanoi(N - 1, PosteApoyo, PosteInicial, PosteDestino);
  }
}
