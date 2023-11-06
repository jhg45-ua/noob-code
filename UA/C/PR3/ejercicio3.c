/*
            PRÁCTICA 3. EJERCICIO 3.
    Para compilar: cc ejercicio3.c -o ejercicio3
    Para ejecutar: ./ejercicio3
    { cc = compilador }
*/
#include <stdio.h>

int main() {
  int precio = 0;
  int opcion;

  // se pide que elija la comida
  printf("Elige lo que quieres para comer:\n");
  printf("1. Pasta (3€)\n");
  printf("2. Carne (5€)\n");
  printf("3. Pescado (7€)\n");
  scanf("%d", &opcion);

  // se comprueba si la opción elegida es correcta ...
  if (opcion < 1 || opcion > 3) {
    // ... si la opción no es correcta, se muestra el mensaje y no se hace nada
    // más
    printf("Opción no correcta\n");
  } else {
    // ... si la opción es correcta se suma el precio de la comida elegida
    switch (opcion) {
    case 1:
      precio += 3;
      break;
    case 2:
      precio += 5;
      break;
    case 3:
      precio += 7;
      break;
    }
    // se pide que elija la bebida
    printf("Elige lo que quieres para beber:\n");
    printf("1. Agua (2€)\n");
    printf("2. Cerveza (3€)\n");
    printf("3. Vino (4€)\n");
    scanf("%d", &opcion);

    // se comprueba si la opción elegida es correcta ...
    if (opcion < 1 || opcion > 3) {
      // ... si la opción no es correcta, se muestra el mensaje y no se hace
      // nada más
      printf("Opción no correcta\n");
    } else {
      // ... si la opción es correcta se suma el precio de la comida elegida
      switch (opcion) {
      case 1:
        precio += 2;
        break;
      case 2:
        precio += 3;
        break;
      case 3:
        precio += 4;
        break;
      }

      // se muestra el precio final de la cena
      printf("El precio de la cena es: %d€\n", precio);
    }
  }

  return 0;
}
