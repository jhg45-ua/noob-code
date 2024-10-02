#include <stdio.h>

int main()
{
    int a, b, incremento;
    char separador;

    printf("Introduce a: ");
    scanf("%d", &a);

    printf("Introduce b: ");
    scanf("%d", &b);

    printf("Introduce el incremento: ");
    scanf("%d", &incremento);

    printf("Introduce el separador: ");
    scanf(" %c", &separador);

    int i = a;

    while (i <= b)
    {
        printf("%d", i);
        i += incremento;
        if (i <= b)
            printf("%c ", separador);

    }

    printf("\n");

    return 0;
}