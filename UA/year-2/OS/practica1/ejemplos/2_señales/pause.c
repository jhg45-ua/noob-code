#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
  pid_t pid;
  pid = fork();
  switch(pid) {
  case -1:
    perror("Error en el fork");
    exit(1);

  case 0:
    printf("Hola, soy el hijo. Espero 2 segundos...\n");
    sleep(2);
    kill(getppid(), SIGUSR1);
    exit(0);

  default:
    printf("Hola, soy el padre y voy a esperar");
    signal(SIGUSR1, SIG_IGN);
    pause();
    printf("Soy el padre y ya he recibido la senal.\n");
    exit(0);
  }
}
