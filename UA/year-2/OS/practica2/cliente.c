#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define DEFAULT_PORT 9999

int main(int argc, char const* argv[])
{
    int socketfd, bytesRecived, filefd;
    struct sockaddr_in serverAddr;
    char buffer[20480]; // 10240 -> 10KB

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <direccion_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        fprintf(stderr, "Error al crear el socket:\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Socket creado con exito\n");

    serverAddr.sin_port = htons(DEFAULT_PORT);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Intentando conectar a %s:9999...\n", argv[1]);

    if (connect(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al conectarn");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Conexion realizada con exito...\n");
    printf("\n===== CONTENIDO DEL ARCHIVO =====\n\n");

    // Crear el archivo donde se guardará el contenido recibido
    filefd = open("Google_recibido.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (filefd == -1) {
        fprintf(stderr, "Error al crear el archivo de destino\n");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Recibiendo archivo...\n");

    // Recibir el contenido del archivo y guardarlo
    while((bytesRecived = read(socketfd, buffer, sizeof(buffer))) > 0) {
        if (write(filefd, buffer, bytesRecived) == -1) {
            fprintf(stderr, "Error al escribir en el archivo\n");
            close(filefd);
            close(socketfd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRecived == -1) {
        fprintf(stderr, "Error al recibir datos\n");
    } else {
        printf("Archivo recibido y guardado como 'Google_recibido.html'\n");
    }

    #ifdef __APPLE__
        system("open Google_recibido.html");
    #elif __linux__
        system("xdg-open Google_recibido.html");
    #endif

    close(filefd);
    close(socketfd);

    return 0;
}
