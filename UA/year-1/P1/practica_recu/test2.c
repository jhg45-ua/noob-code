#include <stdio.h>
#include <string.h>

void invierte(char palabra[])
{
    int tam;
    char aux;

    tam = strlen(palabra);
    int j = tam - 1;

    for (int i = 0; i < tam/2; i++)
    {
        aux = palabra[i];
        palabra[i] = palabra[j];
        palabra[j] = aux;
        j--;
    }
}

void cambia_blanco(char palabra[])
{
    for (int i = 0; i < strlen(palabra); i++)
        if (palabra[i]>='A' && palabra[i]<='Z')
            palabra[i] = ' ';
}

int main()
{
    FILE *fe, *fs;
    char palabra[100];

    fe = fopen("carta_papa_noel.txt", "r");
    fs = fopen("carta_traducida.txt", "w");
    if (fe == NULL || fs == NULL)
    {
        printf("Error en la apertura del fichero\n");
        return -1;
    }

    while (fscanf(fe, "%s", palabra) != EOF)
    {
        invierte(palabra);
        cambia_blanco(palabra);
        fprintf(fs, "%s\n", palabra);
    }

    fclose(fe);
    fclose(fs);
    return 0;
}
