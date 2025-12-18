#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "sim_engine.h"
#include "ficheros.h"

#define WIN_WIDTH 1200
#define WIN_HEIGHT 750
#define Y_BARRA 250
#define ALTO_BARRA 100
#define MARGEN_IZQ 50
#define MARGEN_DER 50

void test_sim();

int main(int argc, char const* argv[])
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Gestomemoria - Memory Simulator");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Memoria m;
    inicializar_memoria(&m);
    
    Proceso procesos[MAX_PROCESOS];
    int num_procesos = cargar_procesos("entrada.txt", procesos);

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
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Opcion A: Paso Manual(Tecla espacio)
        if (IsKeyPressed(KEY_SPACE))
            avanzar_tiempo(&m, procesos, num_procesos, &reloj_sim, algoritmo_actual);

        // Opcion B: Auto Play(Tecla P)
        if (IsKeyPressed(KEY_P))
            auto_play = !auto_play;

        // Logica del auto play
        if (auto_play) {
            tiempo_acumulado += GetFrameTime();
            if (tiempo_acumulado >= velocidad) {
                avanzar_tiempo(&m, procesos, num_procesos, &reloj_sim, algoritmo_actual);
                tiempo_acumulado = 0.0f;
            }
        }

        // Opcion C: Resetear (Tecla R)
        if (IsKeyPressed(KEY_R)) {
            inicializar_memoria(&m);
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

            if (auto_play) DrawText("Auto Play: ON (P para OFF)", 20, 90, 20, DARKGREEN);
            else DrawText("Auto Play: OFF (P para ON)", 20, 90, 20, RED);

            DrawText(TextFormat("Procesos Cargados: %d", num_procesos), 20, 120, 10, DARKGRAY);

            // 2. Dibujar la barra de memoria
            // Escala: Pantalla / Memoria -> WIN_WIDTH / MEMORIA_TOTAL
            float ancho_util = WIN_WIDTH - MARGEN_IZQ - MARGEN_DER;
            float escala = ancho_util / MEMORIA_TOTAL;

            for (int i = 0; i < m.cant_particiones; i++) {
                Particion p = m.particiones[i];

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
                    DrawText(p.nombre_proceso, x + 5, Y_BARRA + 35, 10, BLACK);
                    DrawText(TextFormat("%d", p.tamano), x + 5, Y_BARRA + 50, 10, DARKGRAY);
                }

                // Direccion de memoria (arriba del bloque)
                DrawText(TextFormat("%d", p.dir_inicio), x, Y_BARRA - 15, 10, BLACK);
            }

            // Marca final (2000)
            DrawText("2000", MARGEN_IZQ + ancho_util - 30, Y_BARRA - 15, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    test_sim();

    return 0;
}

void test_sim() {
    Memoria m;
    inicializar_memoria(&m);

    TipoAlgo algoritmo_actual = ALGO_PRIMER_HUECO;
    
    limpiar_log("particiones.txt");
    

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

    int reloj = 0;

    // --- BUCLE DE SIMULACIÓN (10 Instantes) ---
    printf("=== INICIO DE LA SIMULACIÓN COMPLEJA ===\n");
    printf("Memoria Total: %d\n\n", MEMORIA_TOTAL);

    for (int i = 0; i < 11; i++) {
        // Llamamos al motor de tiempo
        avanzar_tiempo(&m, procesos, num_procesos, &reloj, algoritmo_actual);
        
        // Visualizamos la memoria
        printf("MEMORIA: ");
        mostrar_estado(&m); // Mostramos el estado de la memoria con el formato adecuado [0 P1 500]...

        // Visualizamos quién está esperando (Cola de espera)
        printf("COLA ESPERA: ");
        int esperando = 0;
        for(int j=0; j<4; j++) {
            if (!procesos[j].en_memoria && !procesos[j].finalizado && procesos[j].t_llegada <= reloj-1) {
                printf("[%s req:%d] ", procesos[j].nombre, procesos[j].mem_requerida);
                esperando++;
            }
        }
        if(esperando == 0) printf("(Nadie)");
        printf("\n----------------------------------------------------\n");
        
        getchar(); // Descomenta para ir paso a paso con ENTER
    }
}