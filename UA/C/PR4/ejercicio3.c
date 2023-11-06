/*
            PRÁCTICA 4. EJERCICIO 3.
    Para compilar: cc ejercicio3.c -o ejercicio3
    Para ejecutar: ./ejercicio3
    { cc = compilador }
*/
#include <stdio.h>

#define MIN 4  // tamaño mínimo que puede tener la figura
#define MAX 15 // tamaño máximo que puede tener la figura

int main() {
  int tamanyo, // para guardar el tamaño que indica el usuario
      i, j;    // para los contadores de los bucles
  char op;     // para guardar la opción de menú elegida por el usuario

  // bucle principal del programa para mostrar el menú repetidamente hasta que
  // no se elija la opción salir
  do {
    // Se muestra el menú con las opciones
    printf("MENÚ\n");
    printf("1 - Figura 1\n");
    printf("2 - Figura 2\n");
    printf("3 - Figura 3\n");
    printf("0 - Salir\n");

    printf("\nElige opción: ");
    scanf(" %c", &op);

    // se comprueba si la opción elegida es para pintar alguna de las figuras
    if (op >= '1' && op <= '3') {
      // bucle para pedir el tamaño de la figura hasta que sea un valor correcto
      do {
        printf("Introduce el tamaño de la figura (%d-%d): ", MIN, MAX);
        scanf(" %d", &tamanyo);
      } while (tamanyo < MIN || tamanyo > MAX);

      // se comprueba la opción de menú elegida para ver qué figura dibujar
      switch (op) {
      case '1': // Figura 1
        for (i = 0; i < tamanyo; i++) {
          for (j = 0; j < 2 * tamanyo; j++) {
            if ((j >= (tamanyo - 1) - i) && (j < tamanyo + i))
              printf("*");
            else
              printf(" ");
          }
          printf("\n");
        }
        break;
      case '2': // Figura 2
        for (i = 0; i < tamanyo; i++) {
          for (j = 0; j < 2 * tamanyo; j++) {
            if ((j >= (tamanyo - 1) - i) && (j < 2 * tamanyo - i - 1))
              printf("*");
            else
              printf(" ");
          }
          printf("\n");
        }
        break;
      case '3': // Figura 3
        for (i = 0; i < 2 * tamanyo; i++) {
          for (j = 0; j < 2 * tamanyo; j++) {
            if (((j >= (tamanyo - 1) - i) && (j < tamanyo + i) &&
                 (i < tamanyo)) // parte de la condición para la parte superior
                                // (igual a la figura 1)
                ||
                (i >= tamanyo && i - j < tamanyo &&
                 j + i <=
                     3 * (tamanyo -
                          1))) // parte de la condición para la parte inferior
              printf("*");
            else
              printf(" ");
          }
          printf("\n");
        }
        break;
      }
    }
  } while (op != '0'); // si la opción del menú elegida es 0, el bucle se
                       // "rompe" y el programa finaliza

  return 0;
}
