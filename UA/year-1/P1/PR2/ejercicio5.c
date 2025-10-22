/*
            PRÁCTICA 2. EJERCICIO 5.
  Para compilar:  cc ejercicio5.c -o ejercicio5
  Para ejecutar: ./ejercicio5
  { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int capacidadGen;
    float consumoGen;

    printf("Introduce la capacidad del deposito del generador (L): ");
    scanf("%d", &capacidadGen);

    printf("Introduce el consumo medio del generador (L/H): ");
    scanf("%f", &consumoGen);

    float tiempoUso = capacidadGen/consumoGen; // Resultado en horas (con decimales)
    int dias = (int)tiempoUso / 24;
    int horas = (int)tiempoUso % 24;
    int minutos = (int)((tiempoUso - (int)tiempoUso) * 60);

    printf("El generador se mantendrá encendido por:\n %d días, %d horas y %d minutos\n", dias, horas, minutos);
}
