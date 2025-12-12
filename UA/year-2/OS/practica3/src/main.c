#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "engine.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 450

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


    Memoria m;
    inicializar_memoria(&m);
    
    // Simulamos procesos falsos para probar
    Proceso p1 = {"P1", 0, 300, 10, 10, false, false}; // Pide 300
    Proceso p2 = {"P2", 0, 200, 10, 10, false, false}; // Pide 200

    printf("--- FASE 1: LLENADO ---\n");
    ocupar_memoria(&m, 0, p1); // P1 en 0
    ocupar_memoria(&m, 1, p2); // P2 en 300
    mostrar_estado(&m);
    // Esperado: [0 P1 300] [300 P2 200] [500 HUECO 1500]

    printf("\n--- FASE 2: LIBERAR P1 (Fragmentacion) ---\n");
    liberar_proceso(&m, "P1");
    mostrar_estado(&m);
    // Esperado: [0 HUECO 300] [300 P2 200] [500 HUECO 1500]
    // (Nota: No se fusionan porque P2 está en medio estorbando)

    printf("\n--- FASE 3: LIBERAR P2 (Fusion Total) ---\n");
    liberar_proceso(&m, "P2");
    mostrar_estado(&m);
    // Esperado: [0 HUECO 2000]
    // (Explicación: P2 se vuelve hueco -> Se funde con el de izq -> Se funde con el de der)

    return 0;
}