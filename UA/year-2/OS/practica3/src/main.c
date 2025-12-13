#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "engine.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 450

void test_sim() {
    Memoria m;
    inicializar_memoria(&m);

    TipoAlgo algoritmo_actual = ALGO_PRIMER_HUECO;
    
    // Simulamos procesos falsos para probar
    Proceso p1 = {"P1", 0, 300, 10, 10, false, false}; // Pide 300
    Proceso p2 = {"P2", 0, 200, 10, 10, false, false}; // Pide 200
    Proceso p3 = {"P3", 0, 200, 10, 10, false, false}; // Pide 200

    // 1. Llenamos con P1 y P2
    asignar_proceso(&m, p1, algoritmo_actual);
    asignar_proceso(&m, p2, algoritmo_actual);
    
    printf("Estado tras asignar P1 y P2:\n");
    mostrar_estado(&m);
    // [0 P1 300] [300 P2 300] [600 HUECO 1400]

    // 2. Liberamos P1 (creando hueco al inicio)
    liberar_proceso(&m, "P1");
    printf("\nEstado tras liberar P1 (Hueco al inicio):\n");
    mostrar_estado(&m);
    // [0 HUECO 300] [300 P2 300] [600 HUECO 1400]
    
    // --- MOMENTO DE LA VERDAD ---
    // 3. Insertamos P3
    printf("\nIntentando asignar P3...\n");
    asignar_proceso(&m, p3, algoritmo_actual);
    mostrar_estado(&m);

    /* RESULTADOS ESPERADOS:
       
       Si es PRIMER HUECO:
       P3 ocupa el hueco del 0.
       [0 P3 300] [300 P2 300] [600 HUECO 1400]

       Si es SIGUIENTE HUECO:
       El puntero estaba en P2 (300). Busca DESPUÉS de P2.
       Ignora el hueco 0 y se va al final.
       [0 HUECO 300] [300 P2 300] [600 P3 300] [900 HUECO 1100]
    */
}

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