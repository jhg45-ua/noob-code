#include <raylib.h>

#include "sim_engine.h"
#include "ficheros.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 750
#define Y_BARRA 250
#define ALTO_BARRA 100
#define MARGEN_IZQ 50
#define MARGEN_DER 50

void test_sim();
void run_gui(Memoria *m, Proceso *procesos, int num_procesos);

int main(int argc, char const* argv[])
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        return -1;
    }
    else if (pid == 0) {
        // Proceso Hijo: GUI (Raylib)
        Memoria m;
        inicializar_memoria(&m);
        
        Proceso procesos[MAX_PROCESOS];
        int num_procesos = cargar_procesos("entrada.txt", procesos);

        run_gui(&m, procesos, num_procesos);

        // Esperar al hijo que termine
        waitpid(pid, NULL, 0);
    } else {
        // Proceso Padre: TUI (Terminal)
        test_sim();
        _exit(0);
    }

    return 0;
}

/**
 * Prueba del motor de simulación en modo TUI (Terminal User Interface).
 * @return nada
 */
void test_sim() {
    Memoria m;
    inicializar_memoria(&m);

    TipoAlgo algoritmo_actual = ALGO_PRIMER_HUECO;
    
    limpiar_log("particiones_tui.txt");
    

    // // Simulamos procesos falsos para probar
    // Proceso procesos[2] = {
    //     {"P1", 0, 243, 5, 5, false, false}, // ID, Llegada, Tam, Duracion, Restante...
    //     {"P2", 1, 45, 2, 2, false, false}
    //     // {"P3", 2, 500, 5, 5, false, false},
    //     // {"P4", 3, 800, 3, 3, false, false}
    // };

    // Ahora con argumento de fichero
    Proceso procesos[MAX_PROCESOS]; // Maximo 100 procesos
    int num_procesos = cargar_procesos("entrada.txt", procesos);

    int reloj_sim = 0;

    // --- BUCLE DE SIMULACIÓN (10 Instantes) ---
    printf("=== INICIO DE LA SIMULACIÓN COMPLEJA ===\n");
    printf("Memoria Total: %d\n\n", MEMORIA_TOTAL);

    for (int i = 0; i < 11; i++) {
        // Llamamos al motor de tiempo
        avanzar_tiempo(&m, procesos, num_procesos, &reloj_sim, algoritmo_actual, "particiones_tui.txt");
        
        // Visualizamos la memoria
        printf("MEMORIA: ");
        mostrar_estado(&m); // Mostramos el estado de la memoria con el formato adecuado [0 P1 500]...

        // Visualizamos quién está esperando (Cola de espera)
        printf("COLA ESPERA: ");
        int esperando = 0;
        for(int j=0; j<4; j++) {
            if (!procesos[j].en_memoria && !procesos[j].finalizado && procesos[j].t_llegada <= reloj_sim-1) {
                printf("[%s req:%d] ", procesos[j].nombre, procesos[j].mem_requerida);
                esperando++;
            }
        }
        if(esperando == 0) printf("(Nadie)");
        printf("\n----------------------------------------------------\n");
        
        getchar(); // Descomenta para ir paso a paso con ENTER
    }
}

/**
 * Ejecución de la interfaz gráfica usando Raylib.
 * @param m Puntero a la estructura de memoria
 * @param procesos Array de procesos
 * @param num_procesos Número de procesos en el array
 * @return nada
 */
void run_gui(Memoria *m, Proceso *procesos, int num_procesos) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Gestomemoria - Memory Simulator");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    limpiar_log("particiones.txt");

    int reloj_sim = 0;
    TipoAlgo algoritmo_actual = ALGO_PRIMER_HUECO;

    //Variables para repro automatica
    bool auto_play = false;
    float tiempo_acumulado = 0.0f;
    float velocidad = 1.0f; // 1 segundo por tick

    // Main app loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Opcion A: Paso Manual(Tecla espacio)
        if (IsKeyPressed(KEY_SPACE))
            avanzar_tiempo(m, procesos, num_procesos, &reloj_sim, algoritmo_actual, "particiones.txt");

        // Opcion B: Auto Play(Tecla P)
        if (IsKeyPressed(KEY_P))
            auto_play = !auto_play;

        // Logica del auto play
        if (auto_play) {
            tiempo_acumulado += GetFrameTime();
            if (tiempo_acumulado >= velocidad) {
                avanzar_tiempo(m, procesos, num_procesos, &reloj_sim, algoritmo_actual, "particiones.txt");
                tiempo_acumulado = 0.0f;
            }
        }

        // Opcion C: Resetear (Tecla R)
        if (IsKeyPressed(KEY_R)) {
            inicializar_memoria(m);
            num_procesos = cargar_procesos("entrada.txt", procesos);
            reloj_sim = 0;
            limpiar_log("particiones.txt");
            auto_play = false;
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // 1. Textos de informacion
            DrawText("Simulador de Gestion de Memoria", 20, 20, 30, DARKGRAY);
            DrawText(TextFormat("Instante Actual: %d", reloj_sim), 20, 60, 20, BLACK);

            DrawText("Pulsa ESPACIO para avanzar, P para auto play, R para resetear", 20, 120, 20, DARKGRAY);

            if (auto_play) DrawText("Auto Play: ON (P para Desactivar)", 20, 90, 20, DARKGREEN);
            else DrawText("Auto Play: OFF (P para Activar)", 20, 90, 20, RED);
            
            DrawText(TextFormat("Procesos Cargados: %d", num_procesos), 20, 150, 15, DARKGRAY);

            // 2. Dibujar la barra de memoria
            // Escala: Pantalla / Memoria -> WIN_WIDTH / MEMORIA_TOTAL
            float ancho_util = WIN_WIDTH - MARGEN_IZQ - MARGEN_DER;
            float escala = ancho_util / MEMORIA_TOTAL;

            for (int i = 0; i < m->cant_particiones; i++) {
                Particion p = m->particiones[i];

                // Coordenadas
                float x = MARGEN_IZQ + (p.dir_inicio * escala);
                float ancho = p.tamano * escala;

                // Colores: Verde (HUECO) vs Rojo/Azul (Proceso)
                Color colorBloque = (p.estado == 0) ? GREEN : SKYBLUE; // Cambiar colores por pid con un switch

                // Dibujar el rectangulo
                DrawRectangle(x, Y_BARRA, ancho, ALTO_BARRA, colorBloque);
                DrawRectangleLines(x, Y_BARRA, ancho, ALTO_BARRA, Fade(BLACK, 0.5f));

                // Informacion del bloque (si cabe)
                if (ancho > 40) {
                    DrawText(p.nombre_proceso, x + 5, Y_BARRA + 35, 15, BLACK);
                    DrawText(TextFormat("%d", p.tamano), x + 5, Y_BARRA + 50, 15, DARKGRAY);
                }

                // Direccion de memoria (arriba del bloque)
                DrawText(TextFormat("%d", p.dir_inicio), x, Y_BARRA - 15, 15, BLACK);
            }

            // Marca final (2000)
            DrawText("2000", MARGEN_IZQ + ancho_util - 30, Y_BARRA - 15, 15, BLACK);

            // Tablas de procesos
            // -------------------------------------------------------------
        // 3. DIBUJAR TABLA DE PROCESOS (Debajo de la barra de memoria)
        // -------------------------------------------------------------
        int y_inicio_tabla = Y_BARRA + ALTO_BARRA + 40; // Empezamos 40px debajo de la barra
        int x_columna = 20;
        int ancho_columna = 120; // Espacio entre columnas
        
        DrawText("ESTADO DE PROCESOS:", x_columna, y_inicio_tabla - 25, 20, DARKGRAY);

        // Cabecera simple
        // DrawText("ID   Mem   Vida   Estado", x_columna, y_inicio_tabla, 10, BLACK);

        for (int i = 0; i < num_procesos; i++) {
            // Solo dibujamos si cabe en pantalla, si hay muchos habría que hacer paginación
            if (y_inicio_tabla + (i * 20) > WIN_HEIGHT - 20) break;

            // Determinar Color y Estado Texto
            Color colorEstado = LIGHTGRAY;
            const char* textoEstado = "FUTURO";

            if (procesos[i].finalizado) {
                colorEstado = GRAY;     // Gris oscuro para acabados
                textoEstado = "FIN";
            } 
            else if (procesos[i].en_memoria) {
                colorEstado = GREEN;    // Verde para activos
                textoEstado = "ACTIVO";
            } 
            else if (procesos[i].t_llegada <= reloj_sim) {
                colorEstado = RED;      // Rojo para cola de espera
                textoEstado = "ESPERA";
            }
            else {
                colorEstado = LIGHTGRAY; // Gris claro para los que aun no llegan
                textoEstado = TextFormat("T=%d", procesos[i].t_llegada);
            }

            // Dibujamos la fila del proceso
            // Calculamos posición (hacemos varias columnas si hay muchos, opcional)
            int fila_y = y_inicio_tabla + (i * 20); 
            
            // 1. ID y Tamaño
            DrawText(TextFormat("%s (%d)", procesos[i].nombre, procesos[i].mem_requerida), 
                     x_columna, fila_y, 20, BLACK);
            
            // 2. Barra de vida (Pequeña barrita visual)
            if (procesos[i].en_memoria) {
                // Vida restante vs Total
                float porcentaje = (float)procesos[i].t_restante / procesos[i].t_ejecucion;
                DrawRectangle(x_columna + 100, fila_y + 5, 50 * porcentaje, 10, BLUE);
                DrawRectangleLines(x_columna + 100, fila_y + 5, 50, 10, BLACK);
            }

            // 3. Estado (Texto coloreado)
            DrawText(textoEstado, x_columna + 160, fila_y, 20, colorEstado);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}