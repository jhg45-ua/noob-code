#include "file_utils.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/**
 * Escribe todos los bytes del buffer al descriptor.
 * Maneja escrituras parciales.
 *
 * @param fd Descriptor de destino
 * @param buffer Datos a escribir
 * @param size Cantidad de bytes a escribir
 * @return 0 en éxito, -1 en error
 */
int write_all(int fd, const void* buffer, size_t size) 
{
    size_t total_written = 0;
    ssize_t bytes_written;

    while (total_written < size) {
        bytes_written = write(fd, buffer + total_written, size - total_written);
        if (bytes_written == -1) {
            if (errno == EINTR) continue;
            return -1;
        }
        total_written += bytes_written;
    }
    return 0;
}

/**
 * Lee exactamente 'size' bytes de un descriptor.
 * Funciona con buffers, structs o arrays.
 *
 * @param fd Descriptor de origen
 * @param buffer Destino (buffer, struct, array)
 * @param size Bytes a leer
 * @return Bytes leídos, -1 en error, 0 si EOF antes de leer nada
 */
ssize_t read_all(int fd, void *buffer, size_t size) {
    size_t total_read = 0;
    ssize_t bytes_read;
    char *buf = (char *)buffer;

    while (total_read < size) {
        bytes_read = read(fd, buf + total_read, size - total_read);
        if (bytes_read == -1) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (bytes_read == 0)
            break; // EOF
        total_read += bytes_read;
    }
    return total_read;
}


/**
 * Transfiere datos de un descriptor de origen a uno de destino.
 * Funciona con archivos, pipes o sockets.
 *
 * @param fd_src Descriptor de origen (archivo, pipe, socket)
 * @param fd_dst Descriptor de destino (archivo, pipe, socket)
 * @param buffer Buffer para la transferencia
 * @param buffer_size Tamaño del buffer
 * @return Bytes totales transferidos, -1 en caso de error
 */
ssize_t transfer_data(int fd_src, int fd_dst, char *buffer, ssize_t buffer_size) 
{
    ssize_t bytes_read;
    ssize_t total_transfered = 0;

    while((bytes_read = read(fd_src, buffer, buffer_size)) > 0) {
        if (write_all(fd_dst, buffer, bytes_read) == -1)
            return -1;
        total_transfered += bytes_read;
    }
    return (bytes_read == -1 ) ? -1 : total_transfered;
}

/**
 * Lee todo el contenido de un descriptor y lo escribe en otro.
 * Usa un buffer interno si no se proporciona uno.
 *
 * @param fd_src Descriptor de origen
 * @param fd_dst Descriptor de destino
 * @return Bytes totales transferidos, -1 en caso de error
 */
ssize_t transfer_all(int fd_src, int fd_dst) 
{
    char buffer[DEFAULT_BUFFER_SIZE];
    return transfer_data(fd_src, fd_dst, buffer, DEFAULT_BUFFER_SIZE);
}

/**
 * Copia un archivo a otro usando la función de transferencia.
 *
 * @param src_path Ruta del archivo origen
 * @param dst_path Ruta del archivo destino
 * @return Bytes copiados, -1 en error
 */
ssize_t copy_file(const char *src_path, const char *dst_path) 
{
    int fd_src, fd_dst;
    ssize_t result;

    fd_src = open(src_path, O_RDONLY);
    if (fd_src == -1) return -1;

    fd_dst = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC | 0644);
    if (fd_dst == -1) {
        close(fd_dst);
        return -1;
    }

    result = transfer_all(fd_src, fd_dst);

    close(fd_src);
    close(fd_dst);
    return result;
}
