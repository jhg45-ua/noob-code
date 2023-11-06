/*
            PRÁCTICA 3. EJERCICIO 4.
    Para compilar: cc ejercicio4.c -o ejercicio4
    Para ejecutar: ./ejercicio4
    { cc = compilador }
*/
#include <stdio.h>
#include <stdlib.h> // para generar el número aleatorio
#include <time.h>   // para inicializar la semilla de números aleatorios

int main() {
  int aleatorio; // para guardar el número aleatorio
  int j1, j2;    // para guardar los números de los jugadores

  srand(time(NULL)); // inicialización de la semilla de los números aleatorios

  // Se pide el número del primer jugador
  printf("Jugador 1. Introduce un número entre 0 y 100: ");
  scanf("%d", &j1);

  // se comprueba si el número es correcto ...
  if (j1 < 0 || j1 > 100) {
    // si el número no es correcto se muestra el mensaje y no se hace nada más
    printf("El número no es correcto\n");
  } else {
    // si el número es correcto se pide el número al jugador 2
    printf("Jugador 2. Introduce un número entre 0 y 100: ");
    scanf("%d", &j2);

    // se comprueba si el número es correcto ...
    if (j2 < 0 || j2 > 100) {
      // si el número no es correcto se muestra el mensaje y no se hace nada más
      printf("El número no es correcto\n");
    } else {
      // si el número es correcto se saca el número aleatorio y se muestra
      aleatorio = rand() % 99 + 1;
      printf("El número aleatorio es: %d\n", aleatorio);

      // se calcula si la diferencia, en valor absoluto, del número aleatorio
      // con el número del jugador 1 es mayor de 50.
      if (abs(j1 - aleatorio) > 50) {
        // Si lo es, la distancia más corta es el "complementario" a 100 del
        // número
        j1 = 100 - abs(j1 - aleatorio);
      } else {
        // Si no lo es, se deja la distancia calculada
        j1 = abs(j1 - aleatorio);
      }

      // se calcula si la diferencia, en valor absoluto, del número aleatorio
      // con el número del jugador 2 es mayor de 50.
      if (abs(j2 - aleatorio) > 50) {
        // Si lo es, la distancia más corta es el "complementario" a 100 del
        // número
        j2 = 100 - abs(j2 - aleatorio);
      } else {
        // Si no lo es, se deja la distancia calculada
        j2 = abs(j2 - aleatorio);
      }

      // Se muestran las distancias "reales" de los dos jugadores al número
      // aleatorio
      printf("Distancia:\n");
      printf("- Jugador 1: %d\n", j1);
      printf("- Jugador 2: %d\n", j2);

      // Se comprueba cuál de los dos está más cerca y se saca el mensaje
      // correspondiente.
      if (j1 < j2) {
        printf("El ganador es el jugador 1!!\n");
      } else if (j2 < j1) {
        printf("El ganador es el jugador 2!!\n");
      } else {
        printf("No ha ganado ninguno. Ha habido un empate.\n");
      }
    }
  }

  return 0;
}
