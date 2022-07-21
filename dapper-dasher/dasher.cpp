#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{640}, windowHeight{480};

    // Initialize th windows
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1000}; // Gravity - (pixels/s)/s
    const int jumpVel{-600}; // Velocity - pixel/s

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;
    scarfyRect.width = scarfy.width/6;
    scarfyRect.height = scarfy.height;
    scarfyRect.x = 0;
    scarfyRect.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRect.width/2;
    scarfyPos.y = windowHeight - scarfyRect.height;

    int velocity{};

    bool isInAir{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()}; // Delta time

        BeginDrawing();
        ClearBackground(BLACK);

        // Perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRect.height)
        {
            // Rectangle is on ground
            velocity = 0;
            scarfyPos.y = windowHeight - scarfyRect.height;
            isInAir = false;
        }
        else
        {
            // Rectangle is in air
            // Apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump on key press and when on ground
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        
        // update position
        scarfyPos.y += velocity * dT;

        DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}