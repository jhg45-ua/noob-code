#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stddef.h>
#include <sys/types.h>

#define DEFAULT_BUFFER_SIZE 4096

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
ssize_t transfer_data(int fd_src, int fd_dst, char *buffer, ssize_t buffer_size);

/**
 * Lee todo el contenido de un descriptor y lo escribe en otro.
 * Usa un buffer interno si no se proporciona uno.
 *
 * @param fd_src Descriptor de origen
 * @param fd_dst Descriptor de destino
 * @return Bytes totales transferidos, -1 en caso de error
 */
ssize_t transfer_all(int fd_src, int fd_dst);

/**
 * Escribe todos los bytes del buffer al descriptor.
 * Maneja escrituras parciales.
 *
 * @param fd Descriptor de destino
 * @param buffer Datos a escribir
 * @param size Cantidad de bytes a escribir
 * @return 0 en éxito, -1 en error
 */
int write_all(int fd, const char* buffer, size_t size);

/**
 * Copia un archivo a otro usando la función de transferencia.
 *
 * @param src_path Ruta del archivo origen
 * @param dst_path Ruta del archivo destino
 * @return Bytes copiados, -1 en error
 */
ssize_t copy_file(const char *src_path, const char *dst_path);

#endif // FILE_UTILS_H
