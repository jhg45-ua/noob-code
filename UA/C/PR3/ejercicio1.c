/*
                PRÁCTICA 3. EJERCICIO 1.
  Para poder compilar hay que tener los ficheros gfx.h y gfx.c en la misma
  carpeta que ejercicio1.c Para compilar: cc ejercicio1.c gfx.c -o ejercicio1
  -lX11 -lm
  Compilar en Mac: cc example.c gfx.c -o example -I/usr/X11R6/include
  -L/usr/X11R6/lib -lX11 -lm Para ejecutar: ./ejercicio1
  { cc = compilador }
*/
#include "gfx.h" // librería gráfica GFX
#include <stdio.h>

const int ANCHO_VENTANA = 500;
const int ALTO_VENTANA = 500;

int main() {
  char figura;     // 'c' para cuadrado y 'r' para rectángulo
  char c;          // para el bucle de espera de GFX
  int ancho, alto; // para las dimensiones de la figura

  printf("¿Quieres un cuadrado (c) o un rectángulo (r)? ");
  scanf("%c", &figura);

  if (figura == 'r' || figura == 'c') {
    if (figura == 'c') { // cuadrado
      printf("Dime el tamaño del lado: ");
      scanf("%d", &ancho);
      alto = ancho;
    } else { // rectángulo
      printf("Dime el ancho del rectángulo: ");
      scanf("%d", &ancho);
      printf("Dime el alto del rectángulo: ");
      scanf("%d", &alto);
    }
    // DIBUJAR LA FIGURA CORRESPONDIENTE
    // Open a new window for drawing.
    gfx_open(ANCHO_VENTANA, ALTO_VENTANA, "PRACTICA 3. EJERCICIO 1.");

    // Set the current drawing color to green.
    gfx_color(0, 200, 100);

    // Dibujar la figura
    gfx_line(100, 100, 100 + ancho, 100);
    gfx_line(100 + ancho, 100, 100 + ancho, 100 + alto);
    gfx_line(100 + ancho, 100 + alto, 100, 100 + alto);
    gfx_line(100, 100 + alto, 100, 100);

    while (1) {
      // Wait for the user to press a character.
      c = gfx_wait();

      // Quit if it is the letter q.
      if (c == 'q')
        break;
    }
  } else {
    printf("No te entiendo\n");
  }

  return 0;
}
