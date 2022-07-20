#include "raylib.h"

int main()
{
    int width = 320, height = 240;

    InitWindow(width, height, "Axe Game");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawCircle(width/2, height/2, 25, GREEN);

        EndDrawing();
    }
}