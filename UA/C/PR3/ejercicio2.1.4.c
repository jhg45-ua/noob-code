/*
            PRÁCTICA 3. EJERCICIO 2.1.3
    Para compilar: cc ejercicio2.1.3.c -o ejercicio2.1.3
    Para ejecutar: ./ejercicio2.1.3
    { cc = compilador }
*/
#include <stdio.h>

int main() 
{
    int ops, size;

    printf("MENU\n");
    printf("------------\n");
    printf("1 - Figura 1\n");
    printf("2 - Figura 2\n");
    printf("3 - Figura 3\n");
    printf("4 - Figura 4\n");
    printf("5 - Figura 5\n");
    printf("0 - Salir\n");

    printf("Elige una opcion: ");
    scanf("%d", &ops);

    printf("Introduce el tamaño de la figura (4 a 15): ");
    scanf("%d", &size);
    
    switch (ops) {
        case 1:
            for (int i = 1; i <= size; i++) {
                for (int j = 1; j <= i; j++) {
                    printf("*");
                }
                printf("\n");
            }
            break;
        
        case 2:
            printf("Opción 2\n");
            break;

        case 3:
            printf("Opción 3\n");
            break;

        case 4:
            printf("Opción 4\n");
            break;

        case 5:
            printf("Opción 5\n");
            break;

        default:
            printf("Opcion incorrecta\n");
            break;
    }

    return 0;
}
