/*
            PRÁCTICA 3. EJERCICIO 1.6
    Para compilar: cc ejercicio1.6.c -o ejercicio1.6
    Para ejecutar: ./ejercicio1.6
    { cc = compilador }
*/
#include <stdio.h>
#include <math.h>

int main() 
{
    // IMC = peso/(altura*altura) | peso/(pow(altura, 2))
    float peso, altura, imc;

    printf("Introduce el peso (kg): ");
    scanf("%f", &peso);

    printf("Introduce la altura (m): ");
    scanf("%f", &altura);

    imc = peso/pow(altura, 2);

    if (imc < 18.0) // IMC Inferior al Normal
        printf("Valor de IMC: %.2f - Inferior al Normal\n", imc);
    else if (imc >= 18.1 && imc <= 24.9) // IMC Normal 
        printf("Valor de IMC: %.2f - Normal\n", imc);
    else if (imc >= 25.0 && imc <= 29.9)
        printf("Valor de IMC: %.2f - Sobrepeso\n", imc);
    else
        printf("Valor de IMC: %.2f - Obesidad\n", imc);

    

    return 0;
}
