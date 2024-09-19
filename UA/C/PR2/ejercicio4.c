/*
            PRÁCTICA 2. EJERCICIO 4.
  Para compilar:  cc ejercicio4.c -o ejercicio4
  Para ejecutar: ./ejercicio4
  { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    float cantidad;
    int b50e, b20e, b10e, b5e, m2e, m1e, m50cent, m20cent, m10cent, m5cent, m2cent, m1cent;

    printf("Intruduce la cantidad a cambiar (€): ");
    scanf("%f", &cantidad);

    b50e = cantidad / 50; // Cantidad billetes 50
    cantidad = cantidad - b50e*50;
    printf("Billetes de 50€: %d\n", b50e);
    
    b20e = cantidad / 20;
    cantidad = cantidad - b20e*20;
    printf("Billetes de 20€: %d\n", b20e);

    b10e = cantidad / 10;
    cantidad = cantidad - b10e*10;
    printf("Billetes de 10€: %d\n", b10e);

    b5e = cantidad / 5;
    cantidad = cantidad - b5e*5;
    printf("Billetes de 5€: %d\n", b5e);

    m2e = cantidad / 2;
    cantidad = cantidad - m2e*2;
    printf("Monedas de 2€: %d\n", m2e);

    m1e = cantidad / 1;
    cantidad = cantidad - m1e*1;
    printf("Monedas de 1€: %d\n", m1e);

    m50cent = cantidad / 0.50;
    cantidad = cantidad - m50cent*0.50;
    printf("Monedas de 50cent: %d\n", m50cent);

    m20cent = cantidad / 0.20;
    cantidad = cantidad - m20cent*0.20;
    printf("Monedas de 20cent: %d\n", m20cent);

    m10cent = cantidad / 0.10;
    cantidad = cantidad - m10cent*0.10;
    printf("Monedas de 10cent: %d\n", m10cent);

    m5cent = cantidad / 0.05;
    cantidad = cantidad - m5cent*0.05;
    printf("Monedas de 5cent: %d\n", m5cent);

    m2cent = cantidad / 0.02;
    cantidad = cantidad - m5cent*0.02;
    printf("Monedas de 2cent: %d\n", m2cent);

    m1cent = cantidad / 0.01;
    cantidad = cantidad - m1cent*0.01;
    printf("Monedas de 1cent: %d\n", m1cent);

    return 0;
}

// Cantidad = 102€
// b50e => 102/50 = 2
// cantidad = 102 - 2*50