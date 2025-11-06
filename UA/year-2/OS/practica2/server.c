#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const* argv[])
{

    socklen_t size;
    struct sockaddr_in serverAddr, clientAddr;
    int sockfd, clientSocketfd, filefd, bytesRead, bytesSent;
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

        printf("Esperando nuevas conexiones...\n");

        size = sizeof(clientAddr);
        clientSocketfd = accept(sockfd, (struct sockaddr *)&clientAddr, &size);
        if (clientSocketfd == -1) {
            fprintf(stderr, "Error aceptando la conexion\n");
            continue;
        }

        printf("Conexion aceptada!!!\n");

        pid = fork();

        if (pid == 0) {
            close(sockfd);

            printf("El hijo maneja la conexion...\n");

            //Abrimos el archivo
            filefd = open("Google.html", O_RDONLY);
            if (filefd == -1) {
                fprintf(stderr, "Error al abrir el archivo Google.html\n");
                close(clientSocketfd);
                exit(EXIT_FAILURE);
            }

            printf("Enviando el archivo al cliente...\n");

            //Leer y enviar el archivo poco a poco
            while((bytesRead = read(filefd, buffer, sizeof(buffer))) > 0) {
                bytesSent = send(clientSocketfd, buffer, bytesRead, 0);
                if (bytesSent == -1) {
                    fprintf(stderr, "Error en la transferencia del archivo\n");
                    break;
                }
            }

            if (bytesRead == -1)
                fprintf(stderr, "Error al leer el archivo\n");
            else
             printf("Archivo enviado correctamente\n");

            close(filefd);
            close(clientSocketfd);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {
            close(clientSocketfd);
        } else {
            fprintf(stderr, "Error al crear el proceso hijo");
            close(clientSocketfd);
        }
    }

    return 0;
}
