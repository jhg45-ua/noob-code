#include <netinet/in.h> // estructura para almacenar información de dirección
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // para las APIs de socket
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define DEFAULT_PORT 9999
#define BUFFER_SIZE 20480 // 20480

int receiveFile(int socketfd, const char *filename, char *buffer, size_t buffer_size) {
    int bytesReceived;
    int filefd;

    printf("\n===== CONTENIDO DEL ARCHIVO =====\n\n");

    // Crear el archivo donde se guardará el contenido recibido
    filefd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (filefd == -1) {
        fprintf(stderr, "Error al crear el archivo de destino\n");
        return -1;
    }

    printf("Recibiendo archivo...\n");

    // Recibir el contenido del archivo y guardarlo
    while((bytesReceived = read(socketfd, buffer, buffer_size)) > 0) {
        if (write(filefd, buffer, bytesReceived) == -1) {
            fprintf(stderr, "Error al escribir en el archivo\n");
            close(filefd);
            return -1;
        }
    }

    if (bytesReceived == -1) {
        fprintf(stderr, "Error al recibir datos\n");
        close(filefd);
        return -1;
    }

    printf("Archivo recibido y guardado como '%s'\n", filename);

    // Abrir el archivo recibido en el navegador predeterminado en base a macros del sistema operativo
    #ifdef __APPLE__
        system("open Google_recibido.html");
    #elif __linux__
        system("xdg-open Google_recibido.html");
    #endif

    return filefd;
}

int main(int argc, char const* argv[])
{
    int socketfd, filefd; // descriptores de archivo para el socket y el archivo recibido
    struct sockaddr_in serverAddr; // estructura para almacenar información de dirección del servidor
    char buffer[BUFFER_SIZE]; // buffer para almacenar datos recibidos

    // Verificar que se haya proporcionado la dirección IP del servidor
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <direccion_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Crear el socket para la conexión al servidor
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        fprintf(stderr, "Error al crear el socket:\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Socket creado con exito\n");

    // Configurar la estructura sockaddr_in del servidor
    serverAddr.sin_port = htons(DEFAULT_PORT); // puerto del servidor
    serverAddr.sin_family = AF_INET; // familia de direcciones IPv4
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]); // dirección IP del servidor

    printf("Intentando conectar a %s:9999...\n", argv[1]);

    // Conectar al servidor, con gestión de errores
    if (connect(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
        fprintf(stderr, "Error al conectar\n");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    printf("Conexion realizada con exito...\n");

    // Region para probar el tiempo de ejecución de la función receiveFile
    clock_t t;
    t = clock();
    // Usar la función
    filefd = receiveFile(socketfd, "Google_recibido.html", buffer, BUFFER_SIZE);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("receiveFile() tardo %f segundos en ejecutar\n", time_taken);

    // Si hubo un error en la recepción del archivo, cerrar el socket y salir
    if (filefd == -1) {
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    // Cerrar descriptores de archivo y socket
    close(filefd);
    close(socketfd);
    return 0;
}
