/*
            PRÁCTICA 3. EJERCICIO 2.1.2
    Para compilar: cc ejercicio2.1.2.c -o ejercicio2.1.2
    Para ejecutar: ./ejercicio2.2
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int potencia, valor;

    printf("Introduce un numero entero: ");
    scanf("%d", &valor);

    potencia = 1;
    printf("<");
    while(potencia <= valor) 
    {
        printf("%d", potencia);
        potencia = potencia * 2;
        if (potencia <= valor)
            printf(", ");
    }
    printf(">");
    printf("\n");

    return 0;
}
