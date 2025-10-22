#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int i;
    
    printf("\nEjecutando el progarama invocador (prog1). Sus argumentos son: \n");

    for(i = 0; i < argc; i++) {
        printf("    argv[%d]: %s \n", i, argv[i]);
    }

    sleep(10);
    strcpy(argv[0], "prog2");
    if (execvp("./ejemplos/2_señales/prog2", argv) < 0) {
        printf("Error en la invocación a prog2\n");
        exit(1);
    }
    exit(0);
}