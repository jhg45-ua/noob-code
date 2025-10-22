/*
            PRÁCTICA 2. EJERCICIO 3.
  Para compilar:  cc ejercicio3.c -o ejercicio3
  Para ejecutar: ./ejercicio3
  { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    float precioLitro, presupuesto;

    printf("Introduce el precio del litro (€): ");
    scanf("%f", &precioLitro);

    printf("Introduce el presupuesto disponible (€): ");
    scanf("%f", &presupuesto);

    float litrosDisponibles = presupuesto/precioLitro;

    printf("Los litros que puedes poner: %.2fL\n", litrosDisponibles);
}
