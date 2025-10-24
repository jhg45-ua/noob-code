#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Función simple que genera X procesos verticales e Y horizontales
void create_tree(int x, int y, int* X_pointer, int* Y_pointer) {
    int i, proceso;

    // CREAR X PROCESOS EN CADENA VERTICAL
    for (i = 1; i <= x; i++) {
        proceso = fork();

        if (proceso != 0) {
            // El padre espera y termina (no continúa la cadena)
            wait(NULL);
            return;
        }
        // El hijo continúa el bucle para crear el siguiente hijo
    }

    // Si llegamos aquí, somos el último hijo X
    // CREAR Y PROCESOS EN PARALELO (HORIZONTAL)
    for (i = 0; i < y; i++) {
        proceso = fork();

        if (proceso == 0) {
            // Proceso hijo Y - hace su trabajo y termina
            printf("Hijo Y con PID: %d\n", getpid());
            sleep(2);
            exit(0);
        }
    }

    // El último hijo X espera a todos los hijos Y
    for (i = 0; i < y; i++) {
        wait(NULL);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <X> <Y>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    if (x <= 0 || y <= 0) {
        fprintf(stderr, "Error: X e Y deben ser mayores que 0\n");
        return EXIT_FAILURE;
    }

    printf("Superpadre PID: %d\n", getpid());
    //create_tree(x, y);
    printf("Superpadre terminando\n");

    return EXIT_SUCCESS;
}
