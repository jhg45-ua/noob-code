#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../lib/file_utils.h"

int main(int argc, char *argv[]) {
    int pipes[2], file_fd;

    pipe(pipes);

    if (fork() != 0) { // Padre: lee archivo -> escribe en pipe
            close(pipes[0]);
            file_fd = open(argv[1], O_RDONLY);
            transfer_all(file_fd, pipes[1]);
            close(file_fd);
            close(pipes[1]);
        } else { // Hijo: lee de pipe -> escribe en archivo
            close(pipes[1]);
            file_fd = creat(argv[2], 0666);
            transfer_all(pipes[0], file_fd);
            close(file_fd);
            close(pipes[0]);
        }
        return EXIT_SUCCESS;
}
