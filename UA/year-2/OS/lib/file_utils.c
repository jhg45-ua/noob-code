#include "file_utils.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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

ssize_t transfer_all(int fd_src, int fd_dst) 
{
    char buffer[DEFAULT_BUFFER_SIZE];
    return transfer_data(fd_src, fd_dst, buffer, DEFAULT_BUFFER_SIZE);
}

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
