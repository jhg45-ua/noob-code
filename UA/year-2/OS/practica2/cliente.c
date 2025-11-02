#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "Error al crear el socket\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Socket creado con exito\n");

    serverAddr.sin_port = htons(9999);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al conectar\n");
        exit(EXIT_FAILURE);
    }

    printf("Conexion realizada con exito...\n");
    sleep(5);

    return 0;
}
