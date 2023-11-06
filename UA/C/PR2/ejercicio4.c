/*
            PRÁCTICA 2. EJERCICIO 4.
  Para compilar:  cc ejercicio4.c -o ejercicio4
  Para ejecutar: ./ejercicio4
  { cc = compilador }
*/
#include <stdio.h>

int main() {
  int a, b, c; // las tres variables para recoger los tres números
  int aux;     // variable auxiliar para el intercambio

  // Se piden los números al usuario
  printf("Valor de a: ");
  scanf("%d", &a);
  printf("Valor de b: ");
  scanf("%d", &b);
  printf("Valor de c: ");
  scanf("%d", &c);

  printf("Valores antes del intercambio: a=%d  b=%d  c=%d\n", a, b, c);

  // Intercambio
  aux = b;
  b = c;
  c = a;
  a = aux;

  printf("Valores después del intercambio: a=%d  b=%d  c=%d\n", a, b, c);

  return 0;
}
