/*
            PRÁCTICA 3. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/
#include <stdio.h>

int main() {
  float notaPracticas, notaTeoria, notaMedia; // para guardar las notas

  // Se piden ambas notas
  printf("Dime la nota de teoría: ");
  scanf(" %f", &notaTeoria);
  printf("Dime la nota de prácticas: ");
  scanf(" %f", &notaPracticas);

  // Se comprueba las notas introducidas estén entre 0 y 10
  if (notaTeoria < 0 || notaTeoria > 10 || notaPracticas < 0 ||
      notaPracticas > 10) {
    // Si alguna de las notas no es correcta se saca un mensaje y se termina
    printf("Las notas no son correctas, tienen que estar entre 0 y 10.\n");
  } else { // las notas son correctas y se va a calcular la nota final
    // la nota media se calcula en cualquier caso
    notaMedia = (notaTeoria + notaPracticas) / 2;

    // si alguna de las dos notas está por debajo de 4 se comprueba si es mayor
    // que 4.5, en cuyo caso la nota media es 4.5
    if (notaTeoria < 4 || notaPracticas < 4) {
      if (notaMedia >
          4.5) // si la nota media es superior a 4.5, hacemos que sea 4.5
        notaMedia = 4.5;
    }

    // ahora ya podemos sacar el mensaje de la nota media final ...
    printf("Tu nota final es : %.2f - ", notaMedia);

    // ... y le añadimos la nota literal que le corresponde
    if (notaMedia < 5) {
      printf("SUSPENSO");
    } else if (notaMedia < 7) {
      printf("APROBADO");
    } else if (notaMedia < 9) {
      printf("NOTABLE");
    } else {
      printf("SOBRESALIENTE");
    }

    // el salto de línea se podía haber añadido a cada nota literal, pero se ha
    // puesto uno solo aquí
    printf("\n");
  }

  return 0;
}
