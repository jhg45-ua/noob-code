#include "ficheros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include <unistd.h>
#include "../../lib/file_utils.h"

#define SIZE_BUFFER_LECTURA 4096 // Asumimos que el archivo de entrada no pesa más de 4KB

int cargar_procesos(const char* ruta, Proceso procesos[]) {
    // 1. Abrir con open(Unix standard)
    int fd = open(ruta, O_RDONLY);
    if (fd == -1) {
        perror("Error abriendo fichero de entrada");
        return 0;
    }

    // 2. Leer TODO el archivo a un buffer usando file_utils.h
    char buffer_archivo[SIZE_BUFFER_LECTURA];
    memset(buffer_archivo, 0, SIZE_BUFFER_LECTURA); // Limpiamos el buffer para evitar basura

    ssize_t leidos = read_all(fd, buffer_archivo, SIZE_BUFFER_LECTURA - 1);
    close(fd); // Ya tenemos los datos y por tanto cerramos el descriptor
    if (leidos == -1) {
        perror("Error al leer el fichero");
        return 0;
    }

    // 3. Parsear el texto (linea por linea)
    int count = 0;
    char *linea = strtok(buffer_archivo, "\n"); // Primera linea

    while(linea != NULL && count < MAX_PROCESOS) {
        char nombre[10];
        int llegada, mem, ejec;
        // Formato fuente: <Proceso> <Instante_llegada> <Memoria_requerida> <Tiempo_de_ejecuccion>
        if (sscanf(linea, "%s %d %d %d", nombre, &llegada, &mem, &ejec) == 4) {
            // Copiamos al struct Proceso
            strcpy(procesos[count].nombre, nombre);
            procesos[count].t_llegada = llegada;

            // Opcion 1: Aplicamos alinear_size para cumplir con la asignacion de 100 en 100
            // procesos[count].mem_requerida = alinear_size(mem);
            // Opcion 2: La memoria ya se aliena a la hora de asignar el proceso
            procesos[count].mem_requerida = mem;

            procesos[count].t_ejecucion = ejec;
            
            // Inicializacion del estado del proceso
            procesos[count].t_restante = ejec;
            procesos[count].en_memoria = false;
            procesos[count].finalizado = false;

            count++;
        } 
        // Siguiente linea
        linea = strtok(NULL, "\n");
    }
    
    return count;
}

void guardar_estado(const char* ruta, Memoria *m, int instante) {
    // Abrimos el archivo en modo append y CREAT si no existe
    int fd = open(ruta, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error al abrir o crear el archivo");
        return;
    }

    char buffer_linea[1024]; // Buffer temporal

    // Formato fuente: <instante_tiempo> <estado_memoria> \n
    // 1. Escribimos el instante de tiempo
    int len = sprintf(buffer_linea, "%d", instante);
    write_all(fd, buffer_linea, len);

    // 2. Recorremos las particiones
    for (int i = 0; i < m->cant_particiones; i++) {
        Particion p = m->particiones[i];

        // Formateamos una particion al formato requerido
        len = sprintf(buffer_linea, "[%d, %s, %d] ", p.dir_inicio, p.nombre_proceso, p.tamano);
        write_all(fd, buffer_linea, len);
    }

    // 3. Salto de linea final
    write_all(fd, "\n", 1);

    close(fd);
}

void limpiar_log(const char* ruta) {
    // O_TRUNC borra el contenido al abrir
    int fd = open(ruta, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) close(fd);
}