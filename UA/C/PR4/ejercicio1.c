/*
                PRÁCTICA 4. EJERCICIO 1.
    Para poder compilar hay que tener los ficheros gfx.h y gfx.c en la misma
    carpeta que ejercicio1.c Para compilar: cc ejercicio1.c gfx.c -o ejercicio1
    -lX11 -lm
    Compilar en Mac: cc example.c gfx.c -o example -I/usr/X11R6/include
    -L/usr/X11R6/lib -lX11 -lm Para ejecutar: ./ejercicio1
    { cc = compilador }
*/
#include "gfx.h"
#include <stdio.h>

// CONSTANTES
#define ANCHO_VENTANA 300 // ancho de la ventana gráfica
#define ALTO_VENTANA                                                           \
  ANCHO_VENTANA    // alto de la ventana gráfica. Hafo que ea igual al ancho.
#define TAM_MIN 10 // tamaño mínimo del ancho/alto de la figura
#define TAM_MAX                                                                \
  ANCHO_VENTANA - TAM_MIN // tamaño mínimo del ancho/alto de la figura

int main() {
  int xIni, yIni;    // para calcular el pixel (x,y) de la esquina superior
                     // izquierda de la figura y que quede centrada
  int i, j;          // para los bucles
  float alto, ancho; // para guardar el ancho y alto de la figura que introduce
                     // el usuario
  float incrX; // factor de incremento en x con respecto a y para los triángulos

  char c, // para el bucle de gfx que evita que se cierre la ventana
      op; // para recoger la opción de menú de la figura deseada por el usuario

  // Bucle principal para que mientras no elija una opcion correcta siga
  // mostrando el menú
  do {
    // Se muestra el menú
    printf("MENÚ\n");
    printf("------------------------\n");
    printf("1 - Cuadrado\n");
    printf("2 - Rectángulo\n");
    printf("3 - Triángulo rectángulo\n");
    printf("4 - Triángulo equilátero\n");

    printf("\nElige opción (1-4): ");
    scanf(" %c", &op);

    // se comprueba si la opción elegida es correcta ...
    if (op >= '1' && op <= '4') {
      // ... si la opción elegida es correcta se preguntan las dimensiones de la
      // figura bucle para pedir el ancho de la figura mientras no sea un valor
      // correcto
      do {
        printf("\nIntroduce el ancho de la figura (%d - %d): ", TAM_MIN,
               TAM_MAX);
        scanf(" %f", &ancho);
      } while (ancho < TAM_MIN || ancho > TAM_MAX);

      // Si la figura elegida no es un cuadrado hay que pedir la otra dimensión
      if (op != '1') {
        // bucle para pedir el alto de la figura mientras no sea un valor
        // correcto
        do {
          printf("Introduce el alto de la figura (%d - %d): ", TAM_MIN,
                 TAM_MAX);
          scanf(" %f", &alto);
        } while (alto < TAM_MIN || alto > TAM_MAX);
      } else {
        // si la figura es un cuadrado el alto es igual al ancho, no hace falta
        // pedirlo.
        alto = ancho;
      }

      // Se abre la ventana gfx para dibujar
      gfx_open(ANCHO_VENTANA, ALTO_VENTANA, "PRACTICA 4. EJERCICIO 1.");

      // Se selecciona el color verde para el trazo
      gfx_color(0, 200, 100); // Color RGB: red=0; green=200; blue=100

      // SE DIBUJA LA FIGURA
      // se calcula el par (x,y) de la esquina superior izquierda de la figura
      // para que quede centrada en la ventana.
      xIni = (ANCHO_VENTANA - ancho) / 2;
      yIni = (ALTO_VENTANA - alto) / 2;

      // En función de la figura selecciona se hace el dibujo correspondiente
      switch (op) {
      case '1': // cuadrado
        for (i = 0; i < ancho; i++) {
          gfx_line(xIni, yIni + i, xIni + ancho, yIni + i);
        }
        break;
      case '2': // rectángulo
        for (i = 0; i < alto; i++) {
          gfx_line(xIni, yIni + i, xIni + ancho, yIni + i);
        }
        break;
      case '3': // triángulo rectángulo
        // se calcula el incremento en x como el factor entre el ancho y el alto
        incrX = ancho / alto;

        for (i = 0; i < alto; i++) {
          gfx_line(xIni, yIni + i, xIni + (incrX * i), yIni + i);
        }
        break;
      case '4': // triángulo equilátero
        // a la x de la esquina superior izquieda se le suma la mitad del ancho
        // para centrar el triángulo equilátero
        xIni = xIni + ancho / 2;
        // se calcula el incremento en x como el factor entre el ancho y el alto
        incrX = ancho / alto;

        for (i = 0; i < alto; i++) {
          // a diferencia del anterior triángulo, para dibujar éste le quitamos
          // la mitad del ancho al inicio de cada línea para que queden
          // centradas
          gfx_line(xIni - (incrX * i) / 2, yIni + i, xIni + (incrX * i) / 2,
                   yIni + i);
        }
        break;
      }
    }

  } while (op < '1' || op > '4');

  // bucle gfx para que no se cierre la ventana
  while (1) {
    // Espera a que el usuario pulse una tecla o pinche con el ratón en algún
    // punto de la ventana
    c = gfx_wait();

    // si la tecla pulsada es q se cierra la aplicación
    if (c == 'q')
      break;
  }

  return 0;
}
