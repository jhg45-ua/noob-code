#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "sim_engine.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 450

void test_sim();

int main(int argc, char const* argv[])
{
    // InitWindow(WIN_WIDTH, WIN_HEIGHT, "Gestomemoria - Memory Simulator");

    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // // Main app loop
    // while (!WindowShouldClose())    // Detect window close button or ESC key
    // {
    //     // Update
    //     //----------------------------------------------------------------------------------
    //     // TODO: Update your variables here
    //     //----------------------------------------------------------------------------------

    //     // Draw
    //     //----------------------------------------------------------------------------------
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);
    //         DrawText("Welcome to the sim", 190, 200, 20, LIGHTGRAY);

    //     EndDrawing();
    //     //----------------------------------------------------------------------------------
    // }

    // // De-Initialization
    // //--------------------------------------------------------------------------------------
    // CloseWindow();        // Close window and OpenGL context
    // //--------------------------------------------------------------------------------------


    test_sim();

    return 0;
}

void test_sim() {
    Memoria m;
    inicializar_memoria(&m);

    TipoAlgo algoritmo_actual = ALGO_PRIMER_HUECO;
    
    // Simulamos procesos falsos para probar
    Proceso procesos[4] = {
        {"P1", 0, 500, 5, 5, false, false}, // ID, Llegada, Tam, Duracion, Restante...
        {"P2", 1, 500, 2, 2, false, false},
        {"P3", 2, 500, 5, 5, false, false},
        {"P4", 3, 800, 3, 3, false, false}
    };

    int reloj = 0;

    // --- BUCLE DE SIMULACIÓN (10 Instantes) ---
    printf("=== INICIO DE LA SIMULACIÓN COMPLEJA ===\n");
    printf("Memoria Total: %d\n\n", MEMORIA_TOTAL);

    for (int i = 0; i < 10; i++) {
        // Llamamos a tu motor de tiempo
        avanzar_tiempo(&m, procesos, 4, &reloj, algoritmo_actual);
        
        // Visualizamos la memoria
        printf("MEMORIA: ");
        mostrar_estado(&m); // Tu función con formato [0 P1 500]...

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