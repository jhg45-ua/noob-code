/*
            PRÁCTICA 3. EJERCICIO 1.2
    Para compilar: cc ejercicio1.2.c -o ejercicio1.2
    Para ejecutar: ./ejercicio1.2
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int hora;

    printf("Dime la hora del dia (0-23): ");
    scanf("%d", &hora);

    if (hora > 0 && hora < 23)
    {
        if (hora >= 7 && hora <= 14)
            printf("Buenos dias\n");
        else if (hora >= 15 && hora <= 20)
            printf("Buenas tardes\n");
        else
            printf("Buenas noches\n");
    } else
        printf("Introduce una hora entre las 0 y las 23\n");

    return 0;
}
