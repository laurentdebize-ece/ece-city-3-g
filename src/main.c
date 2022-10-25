#include <stdio.h>
#include "raylib.h"

int main() {
    InitWindow(800, 600, "slaut");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
}
