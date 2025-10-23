#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Manejadores de las señales que manda Z:
        - SIGUSR1: comando en base el proceso
        - SIGUSR2: comando sleep
    - Para proceso A y B: pstree
    - Para proceso X e Y: ls

*/

// Funciones manejadoras de señales

// Maneja la señal SIGUSR2, que indica el fin del sleep
void end_sleep() { }

// Maneja la señal SIGUSR1, que ejecuta el comando pstree
void pstree_command() {
    pid_t pid;
    if ((pid = fork()) == 0)
        execlp("pstree", "pstree", NULL);
    else
        wait(NULL);
}

// Maneja la señal SIGUSR1, que ejecuta el comando ls
void ls_command() {
    pid_t pid;
    if ((pid = fork()) == 0)
        execlp("ls", "ls", "-la", NULL);
    else
        wait(NULL);
}

int main(int argc, char* argv[]) {
    pid_t arb, pid_A, pid_B, pid_X, pid_Y, pid_Z, process;

    arb = getpid(); // Pid del Arb
    printf("Soy el proceso arb: mi pid es %d\n", arb);

    process = fork(); // Se crea el proceso A

    // Arb en ejecuccion
    if (process != 0) {
        wait(NULL); // Espera a que termine A
        printf("Soy arb(%d) y muero\n", arb);
    } else { // Proceso A en ejecucion, process == 0
        pid_A = getpid();
        printf("Soy A: mi pid es %d. Mi padre es %d\n", pid_A, arb);

        process = fork(); // Se crea el proceso B
        if (process != 0) {
            signal(SIGUSR1, pstree_command);
            signal(SIGUSR2, end_sleep);

            wait(NULL); // Espera a que termine B

            printf("Soy A(%d) y muero\n", pid_A);
        } else { // Proceso B en ejecuccion
            signal(SIGUSR1, pstree_command);
            signal(SIGUSR2, end_sleep);

            pid_B = getpid();
            printf("Soy B: mi pid es %d. Mi padre es %d. Mi abuelo es %d\n", pid_B, pid_A, arb);

            // Creamos los tres procesos hijos de B: X,Y,Z
            for (int i = 1; i <= 3; i++) {
                process = fork();

                // Se utiliza despues para mandarles señales, ya que Z no conoce los Pid
                // de X e Y
                if (process != 0) {
                    // El proceso B guarda el Pid de X e Y
                    if (i == 1)
                        pid_X = process;
                    if (i == 2)
                        pid_Y = process;
                } else { // Esta en ejecucion los 3 (X, Y, Z)
                    switch (i) {
                    case 1: // Proceso X
                        pid_X = getpid();
                        printf("Soy X: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo "
                               "es %d\n",
                               pid_X,
                               pid_B,
                               pid_A,
                               arb);
                        signal(SIGUSR1, ls_command);
                        signal(SIGUSR2, end_sleep);
                        pause(); // Sirve para esperar a que llegue una señal

                        //pause();

                        printf("Soy X(%d) y muero\n", pid_X);
                        exit(0);
                        break;
                    case 2: // Proceso Y
                        pid_Y = getpid();
                        printf("Soy Y: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo "
                               "es %d\n",
                               pid_Y,
                               pid_B,
                               pid_A,
                               arb);
                        signal(SIGUSR1, ls_command);
                        signal(SIGUSR2, end_sleep);
                        pause();

                        printf("Soy Y(%d) y muero\n", pid_Y);
                        exit(0);
                        break;

                    case 3: // Proceso Z
                        pid_Z = getpid();
                        printf("Soy Z: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo "
                               "es %d\n",
                               pid_Z,
                               pid_B,
                               pid_A,
                               arb);

                        signal(SIGALRM, end_sleep);
                        alarm(atoi(argv[2])); // Preparamos alarma con el tiempo sacado
                                             // del 2ºargumento
                        pause();

                        // Control de Argumentos
                        if (strcmp(argv[1], "A") == 0 || strcmp(argv[1], "B") == 0) {
                            if (strcmp(argv[1], "A") == 0) {
                                kill(pid_A, SIGUSR1); // Se manda la señal a A ya que es el argumento recibido
                            } else {
                                kill(pid_B, SIGUSR1); // Se manda la señal a B ya que es el argumento recibido
                            }

                            signal(SIGALRM, end_sleep); // Cuando suene la alarma, se despierta
                            alarm(1);
                            pause();

                            kill(pid_Y, SIGUSR2); // Ya que habia hecho pause antes
                            kill(pid_X, SIGUSR2); // Se manda la señal a X e Y para que
                                                  // terminen su sleep

                            if (strcmp(argv[1], "A") == 0) {
                                kill(pid_B, SIGUSR2); // Se manda la señal a B para que termine su sleep
                            } else {
                                kill(pid_A, SIGUSR2); // Se manda la señal a A para que termine su sleep
                            }
                        } else if (strcmp(argv[1], "X") == 0 || strcmp(argv[1], "Y") == 0) {
                            if (strcmp(argv[1], "X") == 0) {
                                kill(pid_X, SIGUSR1); // Se le manda la señal a X y no a Y porque X es
                                                  // el primer hijo de B y esta por encima de Y
                            } else {
                                kill(pid_Y, SIGUSR1); // Se le manda la señal a X y no a Y porque X es
                                                  // el primer hijo de B y esta por encima de Y
                            }

                            signal(SIGALRM, end_sleep); // Cuando suene la alarma, se despierta
                            alarm(1);
                            pause();

                            kill(pid_A, SIGUSR2); // Ya que habia hecho pause antes
                            kill(pid_B, SIGUSR2); // Se manda la señal a X e Y para que
                                                  // terminen su sleep

                            if (strcmp(argv[1], "X") == 0) {
                                kill(pid_Y, SIGUSR2); // Se le manda la señal a X y no a Y porque X es
                                                  // el primer hijo de B y esta por encima de Y
                            } else {
                                kill(pid_X, SIGUSR2); // Se le manda la señal a X y no a Y porque X es
                                                  // el primer hijo de B y esta por encima de Y
                            }

                        }
                        printf("Soy Z(%d) y muero\n", pid_Z);
                        exit(0);
                        break;
                    }
                    break;
                }
            }
            // Espera a que terminen los procesos X, Y y Z
            for (int i = 1; i <= 3; i++)
                wait(NULL);

            printf("Soy B(%d) y muero\n", pid_B);
        }
    }
    return 0;
}
