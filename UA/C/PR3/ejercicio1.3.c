/*
            PRÁCTICA 3. EJERCICIO 1.3
    Para compilar: cc ejercicio1.3.c -o ejercicio1.3
    Para ejecutar: ./ejercicio1.3
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    float op1, op2;
    float result;
    char operador;

    printf("Introduce el primer operador: ");
    scanf("%f", &op1);

    printf("Introduce el segundo operador: ");
    scanf("%f", &op2);

    printf("Introduce el operando (+, -, *, /): ");
    scanf(" %c", &operador);


    if (operador == '+')
    {
        result = op1 + op2;
    }

    if (operador == '-')
    {
        result = op1 - op2;
    }

    if (operador == '*')
    {
        result = op1 * op2;
    }

    if (operador == '/')
    {
        result = op1 / op2;
    }

    printf("El resultado de la operación %.2f %c %.2f es: %.2f\n", op1, operador, op2, result);


    return 0;
}
