/*
            PRÁCTICA 2. EJERCICIO 5.
  Para compilar:  cc ejercicio5.c -o ejercicio5
  Para ejecutar: ./ejercicio5
  { cc = compilador }
*/
#include <stdio.h>

int main() {
  int nPiezas;
  int horas, minutos, segundos;

  printf("¿Cuántas piezas caben en la caja? ");
  scanf("%d", &nPiezas);

  // se calcula el número de horas dividiendo por 3600 segundos que tiene una
  // hora
  horas = nPiezas / 3600;
  // los segundos restantes de la operación anterior se dividen por 60 segundos
  // que tiene un minuto para calcular los minutos
  minutos = (nPiezas % 3600) / 60;
  // se calculan los segundos restantes
  segundos = (nPiezas % 3600) % 60;

  printf("Tiempo hasta que se llene el cubo: %dh, %dm y %ds\n", horas, minutos,
         segundos);

  return 0;
}
