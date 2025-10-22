#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t pid; // pROCESSid

    pid = fork();
    switch (pid)
    {
        case -1:
            printf("No se ha podido crear el proceso hijo \n");
            break;
        case 0:
            printf("Soy el hijo, mi PID es %d y mi PPID es %d \n", getpid(), getppid());
            sleep(10); // Se ejecuta de forma simultanea con el padre
            break;
        default:
            printf("Soy el padre, mi PID es %d y el PID de mi hijo es %d \n", getpid(), pid);
            sleep(10); // Se ejecuta de forma simultanea con el hijo
    }
    printf("Final de ejecucion de %d \n", getppid());
    exit(0);
}