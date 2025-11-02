#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const* argv[])
{

    socklen_t size;
    struct sockaddr_in serverAddr, clientAddr;
    int sockfd, newSocketfd, fdfile;
    char buffer[260];
    pid_t pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket creado con exito\n");

    serverAddr.sin_port = htons(9999);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);

    while(1) {
        size = sizeof(clientAddr);
        newSocketfd = accept(sockfd, (struct sockaddr *)&clientAddr, &size);
        if (newSocketfd == -1) {
            fprintf(stderr, "Error aceptando la conexion\n");
            continue;
        }

        printf("Conexion aceptada!!!\n");

        pid = fork();

        if (pid == 0) {
            close(sockfd);

            printf("El hijo maneja la conexion...\n");
            printf("Usa la tecla Ctrl+C para cerrar el servidor\n");

            close(newSocketfd);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {
            close(newSocketfd);
        } else {
            fprintf(stderr, "Error al crear el proceso hijo");
            close(newSocketfd);
        }

        printf("Esperando nuevas conexiones...\n");
    }

    return 0;
}
