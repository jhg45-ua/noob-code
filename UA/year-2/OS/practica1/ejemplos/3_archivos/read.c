#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int df, tam;
    long num;
    char buffer[10];

    df = open("/dev/tty", O_RDONLY);
    if (df < 0) {
        perror("Error al abrir tty");
        exit(-1);
    }

    tam = read(df, buffer, 9);
    if (tam == -1)
        perror("Error de lectura");
    else {
        buffer[tam] = 0;
        num = atoi(buffer);
        printf("Resultado %ld\n", num*2);
    }
    close(df);

}