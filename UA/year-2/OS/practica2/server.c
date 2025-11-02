#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <unistd.h>

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
    fprintf(stdout, "Socket creado con exito\n");

    serverAddr.sin_port = htons(9999);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);

    while(1) {
        pid = fork();

        if (pid == 0) {
            printf("El hijo espera nuevas conexiones...\n");
            size = sizeof(clientAddr);
            newSocketfd = accept(sockfd, (struct sockaddr *)&clientAddr, &size);
            if (newSocketfd == -1) {
                fprintf(stderr, "Error aceptando la conexion");
                exit(EXIT_FAILURE);
            }
            printf("El hijo acepta la conexion...\n");

            sleep(30);
            close(sockfd);
        } else {
            printf("Esperando a que acabe el hijo\n");
            wait(NULL);
        }
    }

    return 0;
}
