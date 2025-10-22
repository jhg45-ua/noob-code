#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int estado, num;

    switch(fork()) {
        case -1:
            perror("Error en fork");
            exit(1);
        
        case 0:
            num = 13;
            printf("Soy el hijo y muero con %d...\n", num);
            sleep(20);
            exit(num);
        
        default:
            wait(&estado);
            printf("Soy el padre");
            if ((estado & 0x7F) != 0)
                printf("Mi hijo ha muerto con una señal\n");
            else
                printf("\nMi hijo ha muerto con exit(%d)\n", (estado>>8) & 0xFF);
            exit(0);
    }
}