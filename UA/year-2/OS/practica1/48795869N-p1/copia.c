#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int pipes[2], file_in, file_out;

    pipe(pipes);

    if (fork() != 0) { // Ejeccucion del padre
        char read_char;
        close(pipes[0]); // Cierra el extremo de lectura del pipe

        file_in = open(argv[1], O_RDONLY); // Abre el archivo de entrada

        // Leemos el archivo hasta que devuelva 0 y por tanto EOF
        while ((read(file_in, &read_char, sizeof(char))) > 0) {
            write(pipes[1], &read_char, sizeof(char)); // Escribimos en el pipe de escritura
        }

        // Cerramos los descriptores
        close(file_in);
        close(pipes[1]);
    } else {
        char write_char;

        close(pipes[1]); // Cierra el extremo de escritura del pipe

        file_out = creat(argv[2], 0666); // Crea el archivo de salida con permisos de lectura y escritura

        // Al igual que en el padre, leemos hasta EOF
        while((read(pipes[0], &write_char, sizeof(char))) > 0) {
            write(file_out, &write_char, sizeof(char)); // Escribimos en el archivo de salida
        }

        // Cerramos los descriptores
        close(file_out);
        close(pipes[0]);
    }
    return EXIT_SUCCESS;
}
