#include "raylib.h"

int main()
{
    // Window dimensions
    int width = 640, height = 480;
    InitWindow(width, height, "Axe Game");

    // Circle co-ordinates
    int circle_x{width/4}, circle_y{height/2};
    int radius = 20;
    // Circle edges

    // Axe co-ordinates
    int axe_x{width/2}, axe_y{};
    int size = 50;
    int direction{10};

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        // Game logic starts
        DrawCircle(circle_x, circle_y, radius, GREEN);

        DrawRectangle(axe_x, axe_y, size, size, RED);

        // Move the axe
        axe_y += direction;
        if (axe_y > (height-size) || axe_y < 0)
        {
            direction = -direction;
        }

        if (IsKeyDown(KEY_D) && circle_x < (width - radius))
        {
            circle_x += 10;
        }

        if (IsKeyDown(KEY_A) && circle_x > radius)
        {
            circle_x -= 10;
        }

        // Game logic ends
        EndDrawing();
    }
}