#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>

struct Robot
{
    char ID[9];
    char color[10];
    int tiempoTrabajo;
};

int robotValidoEnTiempo(struct Robot rob, int vel, int minut)
{
    float Tmax;

    Tmax = (float)rob.tiempoTrabajo / vel;

    if (Tmax >= minut*60)
        return 1;

    return 0;
}

int robotEspeciales(struct Robot vrobots[], int Vtam, int segundos)
{
    int contador = 0;

    FILE *fichero = fopen("ids.txt", "w");
    if (fichero == NULL)
        return -1;

    for (int i = 0; i < Vtam; i++)
    {
        if (strcmp(vrobots[i].color, "naranja") == 0 || strcmp(vrobots[i].color, "rojo") == 0
            && vrobots[i].tiempoTrabajo/2 > segundos)
        {
            fprintf(fichero, "%s\n", vrobots[i].ID);
            contador++;
        }
    }

    fclose(fichero);
    return contador;
}

int main()
{
    int i, total;
    struct Robot v[6] = {{"KALDDF8J", "rojo", 70000}, {"OJADF9JF", "verde", 50000},
                        {"I8EJ3JR8", "naranja", 200000}, {"R983M9L0", "rojo", 40000},
                        {"N7AKD8LV", "azul", 790}, {"J1972112", "verde", 75000}};

    struct Robot r = {"YZEJ3JR8", "verde", 700};

    printf("A: %d\n", robotValidoEnTiempo(r, 1, 10));
    printf("B: %d\n", robotValidoEnTiempo(r, 2, 20));

    total = robotEspeciales(v, 6, 30000);
    if (total == -1)
        printf("Error en el fichero\n");
    else
    printf("Generado fichero con %d robots\n", total);
}
