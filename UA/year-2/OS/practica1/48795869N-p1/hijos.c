#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    int i, childs, x_childs, y_childs, process;

    int *X_pointer, *Y_pointer, shm1, shm2;

    // Comprobacion de argumentos
    if (argc != 3)
        perror("Error -> Solo dos parametros\n");
    else {
        x_childs = atoi(argv[1]);
        y_childs = atoi(argv[2]);

        // Otra comprobacion de argumentos
        if (x_childs <= 0 || y_childs <= 0)
            perror("Error -> X e Y han de ser mayor que 0\n");
        else {
            // Crear memoria compartida para X -> shm1 y Y -> shm2
            shm1 = shmget(IPC_PRIVATE, sizeof(int)*(x_childs+1), IPC_CREAT|0666);
            shm2 = shmget(IPC_PRIVATE, sizeof(int)*y_childs, IPC_CREAT|0666);

            // Punteros a la memoria compartida
            X_pointer = (int *)shmat(shm1, 0, 0);
            Y_pointer = (int *)shmat(shm2, 0, 0);

            // Guardar el PID del superpadre en la primera posicion del array X
            X_pointer[0] = getpid();

            // Crear la rama vertical de x_childs procesos
            for(i = 1; i <= x_childs; i++) {
                process = fork();

                if(process != 0) // El padre sale para que el hijo continue la cadena
                    break;
                else {
                    printf("Soy el subhijo %d, mis padres son: ", getpid());

                    // Imprimir los PIDs de los padres desde el array X
                    for (childs = 0; childs < i; childs++) {
                        printf("%d", X_pointer[childs]);
                        if (childs != i-1) printf(", ");
                    }
                    printf("\n");

                    // Guardar el PID del hijo actual en el array X
                    X_pointer[i] = getpid();
                }
            }

            // Gestion de la rama vertical y el superpadre
            if (i <= x_childs) {
                wait(NULL); // Esperar a que termine el ultimo hijo de X
                            // Para que no se cree la rama Y varias veces

                // Si es el superpadre, imprimir los PIDs de todos los hijos
                if (i == 1) {
                    printf("Soy el superpadre(%d): mis hijos son: ", getpid());

                    for (i = 1; i <= x_childs; i++) {
                        printf("%d", X_pointer[i]);
                        printf(", ");
                    }

                    for (i = 1; i <= y_childs; i++) {
                        printf("%d", Y_pointer[i-1]);
                        if (i < y_childs) printf(", ");
                    }

                    printf("\n");
                } else { // Si no es el superpadre, crear la rama horizontal de y_childs procesos
                    for (i = 1; i <= y_childs; i++) {
                        process = fork();

                        if (process == 0) {
                            Y_pointer[i-1] = getpid();
                            sleep(20);
                            break;
                        }

                        // El padre espera a que terminen todos los hijos de Y
                        if (i == y_childs + 1)
                            for (i = 1; i <= y_childs; i++)
                                wait(NULL);
                    }
                }
            }

        }
    }
    return EXIT_SUCCESS;
}
