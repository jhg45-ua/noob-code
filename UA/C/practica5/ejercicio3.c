/*
            PRÁCTICA 5. EJERCICIO 3.
    Para compilar: cc ejercicio3.c -o ejercicio3
    Para ejecutar: ./ejercicio3
    { cc = compilador }
*/

#include<stdio.h>
#include<stdlib.h> // para utilizar rand() y generar los números pseudoaleatorios
#include<time.h> // para inicializar la secuencia de números aleatorios

// DECLARACIÓN DE MÓDULOS
void generarNumerosAleatorios(int *n1, int *n2, int *n3);
void pedirNumeros(int *num1, int *num2, int *num3);
int pedirNumeroEntre0y9();

int main(){
    int numAle1, numAle2, numAle3; // guardarán los números aleatorios
    int numUsu1, numUsu2, numUsu3; // guardarán los números del usuario

    // inicializar la semilla de números aleatorios
    srand( time( NULL ) );

    // Generamos los números aleatorios
    generarNumerosAleatorios( &numAle1, &numAle2, &numAle3);

    do {
        // Pedimos los números al usuario
        pedirNumeros( &numUsu1, &numUsu2, &numUsu3);

        // Imprimimos los 3 números
        printf("%d    %d    %d    ", numUsu1, numUsu2, numUsu3);

        // COMPROBAMOS LOS NÚMEROS
        // ... primer número
        if( numUsu1 == numAle1 ) {
            printf(" Verde ");
        }
        else if( numUsu1 == numAle2 || numUsu1 == numAle3 ) {
            printf(" Amarillo ");
        }
        else {
            printf( " Rojo ");
        }
        // ... segundo número
        if( numUsu2 == numAle2 ) {
            printf(" Verde ");
        }
        else if( numUsu2 == numAle1 || numUsu2 == numAle3 ) {
            printf(" Amarillo ");
        }
        else {
            printf( " Rojo ");
        }
        // ... tercer número
        if( numUsu3 == numAle3 ) {
            printf(" Verde ");
        }
        else if( numUsu3 == numAle1 || numUsu3 == numAle2 ) {
            printf(" Amarillo ");
        }
        else {
            printf( " Rojo ");
        }
        printf("\n"); // salto de línea
    } while( numUsu1 != numAle1 || numUsu2 != numAle2 || numUsu3 != numAle3 );

    return 0;
}

// DEFINICIÓN DE MÓDULOS
void generarNumerosAleatorios(int *n1, int *n2, int *n3) {
    int num1, num2, num3; // guardarán los números aleatorios generados

    do {
        num1 = rand() % 10;
        num2 = rand() % 10;
        num3 = rand() % 10;
    } while( num1 == num2 || num1 == num3 || num2 == num3 );

    // devolver los números aleatorios en los parámetros de salida correspondientes
    *n1 = num1;
    *n2 = num2;
    *n3 = num3;
}

// Pide números entre 0 y 9 al usuario y comprueba que sean distintos
void pedirNumeros(int *num1, int *num2, int *num3) {
    int n1, n2, n3; // guardarán los números del usuario

    do {
        // pedir primer número
        n1 = pedirNumeroEntre0y9();
        // pedir segundo número
        n2 = pedirNumeroEntre0y9();
        // pedir tercero número
        n3 = pedirNumeroEntre0y9();
        if( n1 == n2 || n1 == n3 || n2 == n3 ) {
            printf("Los números no pueden coincidir.\n");
        }
    } while( n1 == n2 || n1 == n3 || n2 == n3 );

    // devolvemos los números del usuario en los parámetros de salida
    *num1 = n1;
    *num2 = n2;
    *num3 = n3;
}

// Pide al usuario un nçumero entre 0 y 9 y lo comprueba
int pedirNumeroEntre0y9() {
    int numero;

    do {
        printf("Dime un número entre 0 y 9: ");
        scanf("%d", &numero);
    } while( numero < 0 || numero > 9 );

    return numero;
}
