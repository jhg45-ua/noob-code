/*
            PRÁCTICA 2. EJERCICIO 1.
  Para compilar:
    cc ejercicio1.c -o ejercicio1
  ejercicio1 Para compilar con <math.h>:
    cc ejercicio1.c -o ejercicio1 -lm
  Para ejecutar: ./ejercicio1
  { cc = compilador }
*/
#include <math.h> // librería matemática
#include <stdio.h>
#include <stdlib.h> // librería en la que se encuentra la función abs

int main() {

  printf("%d\n", 8 / 16 * 7);
  printf("%.2f\n", 8.0 / 16 * 7); // %.2f imprime sólo 2 decimales
  printf("%g\n", 8.0 / 16 * 7);   // %g imprime sólo los decimales necesarios
  printf("%d\n", 5 % 3 + 5 / 2);
  printf("%f\n", pow(3, abs(-8)) / (9.9 - 5 * 1.5));
  printf("%f\n", sqrt(28) * 5);

  return 0;
}
