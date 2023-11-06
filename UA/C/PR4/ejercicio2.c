/*
            PRÁCTICA 4. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/
#include <stdio.h>

int main() {
  int num,  // para guardar el número del usuario
      i,    // para utilizarla como contador en el bucle determinado
      suma; // guardará la suma de todos los divisores propios del número

  // bucle para pedir un número entero al usuario mientras no sea correcto
  do {
    printf("Dime un número entero positivo: ");
    scanf("%d", &num);
  } while (num < 0);

  // se inicializa la variable suma en la que iremos acumulando los divisores
  // del número. Como mínimo, el 1 es divisor propio y es el primero. Lo sumamos
  // ya y el bucle empieza en 2
  suma = 1;
  printf("Divisores propios de %d: 1", num);

  // bucle determinado para calcular los divisores del número.
  // Se empieza en 2 (el 1 ya está considerado antes) y vamos hasta num/2,
  // incluido. Pasado num/2 no hay más divisores propios.
  for (i = 2; i <= num / 2; i++) {
    if (num % i == 0) {
      // si el número es divisible por el valor del contador de bucle, entonces
      // el valor del contador del bucle es un divisor y hay que acumularlo a la
      // variable suma
      suma += i;
      // se imprime el divisor
      printf(", %d", i);
    }
  }

  // Se imprime el mensaje final ...
  printf("\nEl número %d ", num);

  // ... y si la suma no coincide con el número, no es perfecto y se imprime
  // "NO" ...
  if (suma != num) {
    printf("NO ");
  }

  // ... parte final del mensaje.
  printf("es perfecto\n");

  return 0;
}
