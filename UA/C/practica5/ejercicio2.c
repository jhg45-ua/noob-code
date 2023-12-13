/*
            PRÁCTICA 5. EJERCICIO 2.
    Para compilar: cc ejercicio2.c -o ejercicio2
    Para ejecutar: ./ejercicio2
    { cc = compilador }
*/

#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

int pedirNumero();
bool esDivisor(int, int);
void divisores(int num, int *nDivs, bool *esPrimo);

int main(){
    int num, nDivs;
    bool esPrimo;

    num = pedirNumero();

    printf("El número %d tiene los siguientes divisores: ", num);

    divisores(num, &nDivs, &esPrimo);

    if(!esPrimo)
        printf("Y NO es primo\n");
    else
        printf("Y ES primo\n");

    return 0;
}


int pedirNumero(){
    int num;

    do{
        printf("\nIntroduce un entero positivo > 0: ");
        scanf(" %d", &num);
    }while(num<1);

    return num;
}

bool esDivisor(int num, int d){
    bool divisor;

    if( num % d == 0)
        divisor = true;
    else
        divisor = false;
    
    return divisor;
}

void divisores(int num, int *nDivs, bool *esPrimo){
    int i;

    *nDivs = 1;
    printf("1");
    for(i = 2; i <= num / 2; i++){
        if(esDivisor(num, i)){ // es divisor
            printf(", %d", i);
            (*nDivs)++;
        }
    }
    (*nDivs)++; // el propio número
    printf(", %d\n", num);

    if(*nDivs == 2)
        (*esPrimo) = true;
    else
        (*esPrimo) = false;
}