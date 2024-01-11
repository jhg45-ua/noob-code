/*
            PRÁCTICA 5. EJERCICIO 4.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h>

// Prototipos
void leerParametros(char *sim, char *opt, int *lado); // [X]
void dibujar(char *sim, char *opt, int *size);        // [X]

// Main

int main() {

  char sim, opt;
  int size;

  // printf("opt = %c\n", opt);

  printf("Test\n");

  leerParametros(&sim, &opt, &size);
  printf("Los valores introducidos son: %c, %c, %ix%i\n", sim, opt, size, size);

  dibujar(&sim, &opt, &size);

  return 1;
}

// Funciones
void leerParametros(char *sim, char *opt, int *size) {

  printf("Introduce un simbolo para dibujar: ");
  scanf(" %c", sim);

  printf("Introduce si quieres la figura Rellena o Vacia(R/V): ");
  scanf(" %c", opt);
  while (*opt != 'R' && *opt != 'V') {
    printf("Tu opcion es: %c. Solo se permien opciones R o V\n", *opt);
    printf("Introduce si quieres la figura Rellena o Vacia(R/V): ");
    scanf(" %c", opt);
  }

  printf("Introduce la longitud deseada entre 4-20 pixeles: ");
  scanf("%i", size);
  while (*size < 4 || *size > 20) {
    printf("El valor debe estar entre 4 y 20. Vuelve a introducirlo: ");
    scanf("%i", size);
  }
}

void dibujar(char *sim, char *opt, int *size) {
  int i, j;

  printf("El tamaño del cuadrado sera: %ix%i\n", *size, *size);

  if (*opt == 'R') {
    for (i = 1; i <= *size; i++) {
      for (j = 1; j <= *size; j++) {
        printf("%c", *sim);
      }

      printf("\n");
    }
  } else if (*opt == 'V') {
    for (i = 1; i <= *size; i++) {
      for (j = 1; j <= *size; j++) {
        if (i == 1 || i == *size || j == 1 || j == *size) {
          printf("%c", *sim);
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }
}
