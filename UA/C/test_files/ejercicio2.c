#include <stdio.h>

#define MAX_PALABRAS 6
#define MAX_CARACTERES 60


long long factorial(int n) {
    long long fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

void ej2(int *cantidad) {
    int num;
    *cantidad = 0;

    printf("Introduce un número (0 para terminar): ");
    scanf("%d", &num);

    while(num != 0) {
        printf("Num: %d ", num);
        printf("Prod: %lld\n", factorial(num));
        (*cantidad)++;
        
        printf("Introduce un número (0 para terminar): ");
        scanf("%d", &num);
    }
}


void ej1_proc(char *cadena, int matriz[MAX_PALABRAS][3]) {
    int i = 0;
    int palabra = 0;
    int longitud = 0;
    int inicio = 0;

    //scanf("%[^\n]%*c", cadena);
    printf("Introduce una cadena de caracteres: ");
    fgets(cadena, MAX_CARACTERES, stdin);

    while (cadena[i] != '\0') {
        if (cadena[i] == ' ') {
            matriz[palabra][0] = inicio;
            matriz[palabra][1] = i - 1;
            matriz[palabra][2] = longitud;
            palabra++;
            longitud = 0;
            inicio = i + 1;
        } else {
            longitud++;
        }
        i++;
    }

    matriz[palabra][0] = inicio;
    matriz[palabra][1] = i - 1;
    matriz[palabra][2] = longitud;
}

void ej1_muestra(int matriz[MAX_PALABRAS][3]) {
    printf("Palabra\tInicio\tFin\tLongitud\n");
    for (int i = 0; i < MAX_PALABRAS; i++) {
        printf("%d\t%d\t%d\t%d\n", i+1, matriz[i][0], matriz[i][1], matriz[i][2]);
    }
}

int main() {
    char cadena[MAX_CARACTERES];
    int matriz[MAX_PALABRAS][3] = {0};
    int cantidad;

    ej1_proc(cadena, matriz);
    ej1_muestra(matriz);

    ej2(&cantidad);
    return 0;
}
