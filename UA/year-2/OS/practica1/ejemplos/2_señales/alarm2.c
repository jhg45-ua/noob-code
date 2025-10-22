#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void alarma();

int main()
{
    signal(SIGALRM, alarma);
    printf("Acabo de programar la captura de un SIGALARM\n");
    alarm(3);
    printf("Ahora he programado la alarma en 3seg\n");
    pause();
    printf("Ahora continuo con la ejecucción normal\n");
}

void alarma()
{
    printf("acabo de recibir un SIGALARM\n");
}