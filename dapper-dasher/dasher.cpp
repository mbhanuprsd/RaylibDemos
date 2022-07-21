#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{640}, windowHeight{480};

    // Initialize th windows
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1};
    const int jumpVel = -22;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;
    Vector2 scarfyPos;

    // Rectangle dimensions
    const int rectWidth{50}, rectHeight{80};

    int rectX{windowWidth / 2 - rectWidth / 2}, rectY{windowHeight - rectHeight};

    int velocity{};

    bool isInAir{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Perform ground check
        if (rectY >= windowHeight - rectHeight)
        {
            // Rectangle is on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in air
            // Apply gravity
            velocity += gravity;
            isInAir = true;
        }

        // Jump on key press and when on ground
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        
        // update position
        rectY += velocity;

        DrawRectangle(rectX, rectY, rectWidth, rectHeight, BLUE);

        EndDrawing();
    }
    CloseWindow();
}