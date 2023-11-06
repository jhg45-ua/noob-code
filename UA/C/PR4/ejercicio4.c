/*
            PRÁCTICA 4. EJERCICIO 4.
    Para compilar: cc ejercicio4.c -o ejercicio4 -lm
    Para ejecutar: ./ejercicio4
    { cc = compilador }
*/
#include <math.h> // para poder utilizar la función pow(base, exp)
#include <stdio.h>

int main() {
  int num;           // número del usuario
  int numSalida,     // número de salida
      numAux;        // número auxiliar para cálculos
  int cifraMenor,    // cifra menor en el número
      posCifraMenor; // posición de la cifra menor en el número (0 la posición
                     // más a la derecha)
  int cifra,   // guardará la cifra extraía en cada iteración
      pos;     // para llevar la posición de la cifra que se está analizando
  char seguir; // guardará la respuesta del usuario a la pregunta de si quiere
               // seguir

  do {
    // bucle para asegurar que el número es un entero positivo
    do {
      printf("Dime un número entero positivo: ");
      scanf("%d", &num);
    } while (num < 1);

    // inicializamos el número de salida. Al final estará formado por todas las
    // cifras del número original, pero ordenadas de menor a mayor
    numSalida = 0;

    // bucle para ordenar todas las cifras del número de menor a mayor
    do {
      numAux = num; // para no perder el número original
      // cogemos la primera cifra del número como la más pequeña
      cifraMenor = num % 10;
      posCifraMenor = 0;
      num = num / 10; // le quito la primera cifra al número

      // mientras num > 0 busco la cifra menor
      pos = 1; // posición de la cifra que estamos analizando
      while (num > 0) {
        cifra = num % 10; // sacamos la cifra de más a la derecha
        num = num / 10;   // quito la cifra de más a la derecha
        if (cifra < cifraMenor) {
          cifraMenor = cifra;
          posCifraMenor = pos;
        }
        pos++; // siguiente cifra
      }

      // esta línea de código es sólo para ver en cada iteración el número, la
      // cifra menor y la posición que ocupa
      printf("Número: %5d - Cifra menor: %d y posición: %d\n", numAux,
             cifraMenor, posCifraMenor);

      // construimos el número de salida añadiéndole la cifra menor recién
      // obtenida
      numSalida = numSalida * 10 + cifraMenor;

      // ==============================================
      // Quitamos la cifra menor del número original:
      // ==============================================
      // 1) restauramos el valor del número original
      num = numAux;
      // 2) cogemos la parte izquierda del número original, con respecto a la
      // cifra menor
      numAux = num / pow(10, posCifraMenor + 1);
      // 3) multiplicamos por la potenica de 10 correspondiente a la posición en
      // la que estaba la cifra menor
      numAux = numAux * pow(10, posCifraMenor);
      // 4) le sumamos a numAux la parte derecha del número original, con
      // respecto a la cifra menor
      numAux = numAux +
               num % (int)(pow(10, posCifraMenor)); // (int) casting: conversión
                                                    // de un número float a int
      // 5) guardamos en num el nuevo número para la siguiente iteración, que es
      // el recién calculado en numAux
      num = numAux;
    } while (num > 0); // mientras num sea mayor que 0 significa que todavía
                       // quedan cifras en el número

    // Se imprime el número de salida en el que están todas las cifras del
    // número original, pero ordenadas de menor a mayor
    printf("El número de salida con las cifras ordenadas es: %d\n", numSalida);

    printf("¿Quieres introducir otro número? (S/N) ");
    scanf(" %c", &seguir);

  } while (seguir == 's' || seguir == 'S');

  return 0;
}
