#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void alarma() { printf("Acabo de recibir la SIGALRM. "); }

int main() 
{
    signal(SIGALRM, alarma);
    printf("Acabo de programar la captura de un SIGALRM\n"); 
    alarm(3); 
    printf("Ahora he programado la alarma en 3 seg.\n"); 
    pause(); 
    printf("Ahora continúo con la ejecución normal\n");

    return 0;
}