#include <stdio.h>

struct medicion
{
    unsigned short anio;
    unsigned char mes;
    unsigned char dia;
    float temperatura;
    unsigned char uv;
    unsigned char viento;
};

void print_medicion(struct medicion *medicion)
{
    printf("Fecha: %d-%d-%d, Registro %fºC. UV %d, Viento %d km/h\n",
            medicion->anio, medicion->mes, medicion->dia,
            medicion->temperatura, medicion->uv, medicion->viento);
}


int main(int argc, char const *argv[])
{
    struct medicion medida;

    FILE *fptr = fopen("temperatura.bin", "rb");
    int total = fread(&medida, sizeof(struct medicion), 1, fptr);
    if(total != 1)
        printf("Hemos tenido un problema");

    fclose(fptr);

    print_medicion(&medida);
}