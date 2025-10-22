#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
    int df, count=0;
    char buffer[128];

    df = creat("variables.txt", 0755);
    if (df < 0) {
        perror("Error al crear archivo");
        exit(-1);
    }

    while ((env[count] != NULL) && (count<20)) {
        strcpy(buffer, env[count]);
        strcat(buffer, "\n");
        if (write(df, buffer, strlen(buffer)) != strlen(buffer)) {
            perror("Error al escribir");
            break;
        }
        count++;
    }
    close(df);
}