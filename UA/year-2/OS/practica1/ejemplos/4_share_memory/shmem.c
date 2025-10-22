#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid, estado;
int *numero = NULL;

int creaMemComp(int tam) {
    if ((shmid=shmget(IPC_PRIVATE, tam, IPC_CREAT|0666)) == -1) {
        perror("Memoria compartida no creada");
        return 1;
    }

    numero = (int *) shmat(shmid, 0, 0);
    *numero = 0;
}

int main(int argc, char *argv[]) {
    int pid, pid0;

    pid0 = getpid();
    creaMemComp(sizeof(int));
    if ((pid = fork() == 0)){
        sleep(3);
        printf("*** Proceso hijo %d, pid del padre: %d y numero: %d\n", getpid(), getppid(), *numero);
        exit(0);
    } else {
        printf("Proceso principal, su pid es %d, pid del hijo %d y num %d\n", getpid(), pid, *numero=getpid());
        wait(&estado);
    }

    return 0; 
}