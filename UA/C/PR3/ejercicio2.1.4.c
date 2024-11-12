/*
            PRÁCTICA 3. EJERCICIO 2.1.4
    Para compilar: cc ejercicio2.1.4.c -o ejercicio2.1.4
    Para ejecutar: ./ejercicio2.1.4
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
        case 1: // Piramide
        	for (int i = 1; i <= size; i++) {
        		for (int j = 1; j <= i; j++) {
                		printf("*");
                	}
                	printf("\n");
            	}
        	break;
        
        case 2: // Triangulo
        	for (int i = 0; i < size; i++) {
			for (int j = 0; j < 2 * size; j++) {
				if (j > i && j < 2 * size - i)
					printf("*");
				else
					printf(" ");	
			}
			printf("\n");
		}
        	break;

        case 3: // Piramide espejo
        	for (int i = 0; i < size; i++) {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (j <= i || j >= 2 * size - 2 - i)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
            	break;

        case 4: // Flecha
        	for (int i = 0; i < 2 * size - 1; i++) {
			for (int j = 0; j < 2 * size; j++) {
				if ((i < size && j >= size - 1 - (i % size) && j < 2 * size - (i % size) - 1)
					|| (i == size - 1 && j < 2 * size - 1)
					|| (i >= size && j > i - size && j < i + 1)
				)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
		break;

        case 5: // Rombo
            	for (int i = 1; i <= size; i++) {
			printf("%*s", size - i + 1, "");
			for (int j = 0; j < 2 * i - 1; j++) {
				printf("*");
			}
			printf("\n");
		}

		for (int i = size - 1; i > 0; i--) {
			printf("%*s", size - i + 1, "");
			for (int j = 0; j < 2 * i - 1; j++) {
				printf("*");
			}
			printf("\n");
		}
		break;

        default:
            printf("Opcion incorrecta\n");
            break;
    }

    return 0;
}
