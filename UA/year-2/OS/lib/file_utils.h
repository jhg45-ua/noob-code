#ifndef FILE_UTILS_H
#define FILE_UTILS_H

/**
 * @file file_utils.h
 * @brief Librería de utilidades para operaciones de E/S con descriptores de fichero.
 * 
 * Este módulo proporciona funciones robustas para:
 * - Lectura/escritura completa de datos (manejo de escrituras parciales)
 * - Transferencia de datos entre descriptores (archivos, pipes, sockets)
 * - Copia de archivos
 * 
 * Todas las funciones manejan correctamente:
 * - Interrupciones del sistema (EINTR)
 * - Escrituras/lecturas parciales
 * - Condiciones de EOF
 * 
 * @author Julian Hinojosa Gil
 * @date 2025
 * @version 1.0
 * 
 * @note Librería externa reutilizable en múltiples prácticas del curso OS.
 * 
 * @example
 * @code
 * // Ejemplo de uso para leer un archivo completo
 * int fd = open("archivo.txt", O_RDONLY);
 * char buffer[1024];
 * ssize_t leidos = read_all(fd, buffer, sizeof(buffer));
 * close(fd);
 * 
 * // Ejemplo de copia de archivo
 * ssize_t bytes = copy_file("origen.txt", "destino.txt");
 * @endcode
 */

#include <stddef.h>
#include <sys/types.h>

/** @defgroup constantes Constantes de Configuración
 *  Valores por defecto para las operaciones de E/S.
 *  @{
 */

/** @brief Tamaño del buffer interno usado por transfer_all() (4KB) */
#define DEFAULT_BUFFER_SIZE 4096

/** @} */

/** @defgroup escritura Funciones de Escritura
 *  Funciones para escritura robusta en descriptores.
 *  @{
 */

/**
 * @brief Escribe todos los bytes del buffer al descriptor de fichero.
 * 
 * Garantiza que se escriban exactamente `size` bytes, manejando
 * automáticamente las escrituras parciales que pueden ocurrir con
 * pipes, sockets o cuando el kernel interrumpe la operación.
 *
 * @param[in] fd Descriptor de fichero de destino (debe estar abierto para escritura)
 * @param[in] buffer Puntero a los datos a escribir
 * @param[in] size Cantidad de bytes a escribir
 * 
 * @return 0 si se escribieron todos los bytes correctamente
 * @return -1 si hubo error (errno contiene el código de error)
 * 
 * @pre fd debe ser un descriptor válido abierto para escritura
 * @pre buffer != NULL
 * @pre size > 0
 * 
 * @note Maneja automáticamente EINTR (interrupciones del sistema)
 * @note Reintenta automáticamente en caso de escrituras parciales
 * 
 * @see read_all()
 */
int write_all(int fd, const void* buffer, size_t size);

/** @} */

/** @defgroup lectura Funciones de Lectura
 *  Funciones para lectura robusta desde descriptores.
 *  @{
 */

/**
 * @brief Lee hasta `size` bytes de un descriptor a un buffer.
 * 
 * Intenta leer exactamente `size` bytes, manejando lecturas parciales
 * y condiciones de EOF. Funciona con cualquier tipo de descriptor:
 * archivos regulares, pipes, sockets, etc.
 *
 * @param[in] fd Descriptor de fichero de origen (debe estar abierto para lectura)
 * @param[out] buffer Destino donde se almacenarán los datos leídos
 * @param[in] size Cantidad máxima de bytes a leer
 * 
 * @return Número de bytes realmente leídos (puede ser menor que size si se alcanzó EOF)
 * @return 0 si se alcanzó EOF antes de leer ningún byte
 * @return -1 si hubo error (errno contiene el código de error)
 * 
 * @pre fd debe ser un descriptor válido abierto para lectura
 * @pre buffer != NULL
 * @pre size > 0
 * 
 * @post Los datos leídos se almacenan en buffer[0..retorno-1]
 * 
 * @note Maneja automáticamente EINTR (interrupciones del sistema)
 * @note Compatible con buffers, structs o arrays de cualquier tipo
 * 
 * @warning El buffer debe tener espacio suficiente para `size` bytes
 * 
 * @see write_all()
 */
ssize_t read_all(int fd, void *buffer, size_t size);

/** @} */

/** @defgroup transferencia Funciones de Transferencia
 *  Funciones para mover datos entre descriptores.
 *  @{
 */

/**
 * @brief Transfiere datos de un descriptor de origen a uno de destino.
 * 
 * Lee todos los datos disponibles de `fd_src` y los escribe en `fd_dst`
 * usando el buffer proporcionado. Funciona con archivos, pipes o sockets.
 *
 * @param[in] fd_src Descriptor de origen (archivo, pipe, socket)
 * @param[in] fd_dst Descriptor de destino (archivo, pipe, socket)
 * @param[in,out] buffer Buffer temporal para la transferencia (proporcionado por el usuario)
 * @param[in] buffer_size Tamaño del buffer en bytes
 * 
 * @return Número total de bytes transferidos exitosamente
 * @return -1 si hubo error de lectura o escritura
 * 
 * @pre fd_src debe estar abierto para lectura
 * @pre fd_dst debe estar abierto para escritura
 * @pre buffer != NULL
 * @pre buffer_size > 0
 * 
 * @note Para mejor rendimiento, usar buffer_size >= DEFAULT_BUFFER_SIZE
 * @note Continúa hasta EOF del descriptor origen
 * 
 * @see transfer_all()
 */
ssize_t transfer_data(int fd_src, int fd_dst, char *buffer, ssize_t buffer_size);

/**
 * @brief Transfiere todo el contenido de un descriptor a otro.
 * 
 * Versión simplificada de transfer_data() que usa un buffer interno
 * de tamaño DEFAULT_BUFFER_SIZE. Ideal para casos donde no se necesita
 * control sobre el tamaño del buffer.
 *
 * @param[in] fd_src Descriptor de origen
 * @param[in] fd_dst Descriptor de destino
 * 
 * @return Número total de bytes transferidos
 * @return -1 si hubo error
 * 
 * @pre fd_src debe estar abierto para lectura
 * @pre fd_dst debe estar abierto para escritura
 * 
 * @note Usa buffer interno de DEFAULT_BUFFER_SIZE (4KB)
 * 
 * @see transfer_data(), copy_file()
 */
ssize_t transfer_all(int fd_src, int fd_dst);

/** @} */

/** @defgroup archivos Funciones de Archivos
 *  Funciones de alto nivel para operaciones con archivos.
 *  @{
 */

/**
 * @brief Copia un archivo completo a otra ubicación.
 * 
 * Abre el archivo origen, crea (o trunca) el archivo destino,
 * transfiere todo el contenido y cierra ambos descriptores.
 *
 * @param[in] src_path Ruta del archivo origen (debe existir y ser legible)
 * @param[in] dst_path Ruta del archivo destino (se crea si no existe, se trunca si existe)
 * 
 * @return Número de bytes copiados exitosamente
 * @return -1 si hubo error (no se pudo abrir origen, crear destino, o error de transferencia)
 * 
 * @pre src_path debe apuntar a un archivo existente y legible
 * @pre El directorio padre de dst_path debe existir
 * 
 * @post El archivo destino contiene una copia exacta del origen
 * @post Los permisos del archivo destino son 0644 (rw-r--r--)
 * 
 * @note Si dst_path existe, su contenido se sobrescribe
 * @warning No copia permisos ni metadatos del archivo original
 * 
 * @par Ejemplo:
 * @code
 * ssize_t bytes = copy_file("/tmp/origen.txt", "/tmp/copia.txt");
 * if (bytes == -1) {
 *     perror("Error copiando archivo");
 * } else {
 *     printf("Copiados %zd bytes\n", bytes);
 * }
 * @endcode
 * 
 * @see transfer_all()
 */
ssize_t copy_file(const char *src_path, const char *dst_path);

/** @} */

#endif // FILE_UTILS_H
