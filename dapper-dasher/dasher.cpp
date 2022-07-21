#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{640}, windowHeight{480};

    // Initialize th windows
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1000}; // Gravity - (pixels/s)/s

    // Scarfy's parameters
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect{0, 0, scarfy.width / 6, scarfy.height};
    Vector2 scarfyPos{windowWidth / 2 - scarfyRect.width / 2, windowHeight - scarfyRect.height};
    int velocity{};
    const int jumpVel{-600}; // Velocity - pixel/s
    bool isInAir{};
    const float scarfyUpdateTime{1.0 / 12.0}; // animation frame time
    float scarfyRunningTime{};
    int scarfyFrame{}; // animation frame

    // Nebula's parameters
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    const int nebVel{-300}; // Velocity - pixel/s
    int nebFrame{};
    const float nebUpdateTime{1.0 / 12.0}; // animation frame time
    float nebRunningTime{};

    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()}; // Delta time

        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check for scarfy
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

        // Perform out of screen for nebula
        if (nebPos.x < -nebRec.width)
        {
            nebPos.x = windowWidth;
        }

        // Jump on key press and when on ground
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update scarfy position
        scarfyPos.y += velocity * dT;
        // update nebula position
        nebPos.x += nebVel * dT;

        // update scarfy animation frame
        if (!isInAir)
        {
            scarfyRunningTime += dT;
            if (scarfyRunningTime >= scarfyUpdateTime)
            {
                scarfyRunningTime = 0;
                // Update scarfy animation frame
                scarfyRect.x = scarfyFrame * scarfyRect.width;
                scarfyFrame++;
                if (scarfyFrame > 5)
                {
                    scarfyFrame = 0;
                }
            }
        }

        // update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0;
            // Update nebula animation frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
