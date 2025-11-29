#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define DEFAULT_PORT 9999
#define BUFFER_SIZE 20480 // 20480

int main(int argc, char const* argv[])
{
    socklen_t size; // tamaño de la estructura sockaddr_in
    struct sockaddr_in serverAddr, clientAddr; // estructuras para almacenar información de dirección del servidor y del cliente
    int sockfd, clientSocketfd, filefd, bytesRead, bytesSent; // descriptores de archivo y contadores de bytes leídos/enviados
    char buffer[BUFFER_SIZE]; // buffer para almacenar datos del archivo
    pid_t pid; // ID del proceso para manejo de conexiones concurrentes

    // Creación del socket, se gestiona el error si no se puede crear
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket creado con exito\n");

    // Configuración de la estructura sockaddr_in
    serverAddr.sin_port = htons(DEFAULT_PORT); // puerto del servidor
    serverAddr.sin_family = AF_INET; // familia de direcciones IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY; // aceptar conexiones en cualquier interfaz de red

    // Enlazar el socket a la dirección y puerto especificados, con gestión de errores
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    // Poner el socket en modo escucha para aceptar conexiones entrantes, maximo 5 conexiones en cola
    listen(sockfd, 5);

    printf("Esperando nuevas conexiones...\n");

    // Bucle infinito para aceptar y manejar conexiones entrantes
    while(1) {
        // Aceptar una nueva conexión de cliente
        size = sizeof(clientAddr);
        clientSocketfd = accept(sockfd, (struct sockaddr *)&clientAddr, &size);
        if (clientSocketfd == -1) {
            fprintf(stderr, "Error aceptando la conexion\n");
            continue;
        }

        printf("Conexion aceptada!!!\n");

        // Crear un proceso hijo para manejar la conexión del cliente
        pid = fork();

        // Dentro del proceso hijo se maneja la transferencia del archivo
        if (pid == 0) {
            close(sockfd);

            printf("El hijo maneja la conexion...\n");
            printf("Usa la tecla Ctrl+C para cerrar el servidor\n");

            //Abrimos el archivo
            filefd = open("Google.html", O_RDONLY);
            if (filefd == -1) {
                fprintf(stderr, "Error al abrir el archivo Google.html\n");
                close(clientSocketfd);
                exit(EXIT_FAILURE);
            }

            printf("Enviando el archivo al cliente...\n");

            //Leer y enviar el archivo por trozos en base al tamaño del buffer
            while((bytesRead = read(filefd, buffer, sizeof(buffer))) > 0) {
                bytesSent = write(clientSocketfd, buffer, bytesRead);
                if (bytesSent == -1) {
                    fprintf(stderr, "Error en la transferencia del archivo\n");
                    break;
                }
            }

            // Verificar si hubo un error al leer el archivo
            if (bytesRead == -1)
                fprintf(stderr, "Error al leer el archivo\n");
            else
                printf("Archivo enviado correctamente\n\n");

            // Cerrar descriptores de archivo y socket
            close(filefd);
            close(clientSocketfd);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {
            close(clientSocketfd);
        } else {
            fprintf(stderr, "Error al crear el proceso hijo");
            close(clientSocketfd);
        }
        // Volver a esperar nuevas conexiones
        printf("Esperando nuevas conexiones...\n");
    }

    return 0;
}
