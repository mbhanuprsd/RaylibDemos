#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window dimensions
    const int windowWidth{640}, windowHeight{480};

    // Initialize th windows
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    const int gravity{1000}; // Gravity - (pixels/s)/s

    // Scarfy's parameters
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0, 0, scarfy.width / 6, scarfy.height},
        {windowWidth / 2 - scarfy.width / 12, windowHeight - scarfy.height},
        0,
        1.0 / 12.0,
        0.0};

    int velocity{};
    const int jumpVel{-600}; // Velocity - pixel/s
    bool isInAir{};

    // Nebula's parameters
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData neb1Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {windowWidth, windowHeight - nebula.height / 8},
        0,
        1.0 / 12.0,
        0.0};

    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {windowWidth * 1.7, windowHeight - nebula.height / 8},
        0,
        1.0 / 16 / 0,
        0.0};

    const int nebVel{-300}; // Velocity - pixel/s

    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()}; // Delta time

        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check for scarfy
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
        {
            // Rectangle is on ground
            velocity = 0;
            scarfyData.pos.y = windowHeight - scarfyData.rec.height;
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
        if (neb1Data.pos.x < -neb1Data.rec.width)
        {
            neb1Data.pos.x = windowWidth;
        }

        // Perform out of screen for second nebula
        if (neb2Data.pos.x < -neb2Data.rec.width)
        {
            neb2Data.pos.x = windowWidth;
        }

        // Jump on key press and when on ground
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dT;
        // update nebula position
        neb1Data.pos.x += nebVel * dT;
        // update second nebula position
        neb2Data.pos.x += nebVel * dT;

        // update scarfy animation frame
        if (!isInAir)
        {
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0;
                // Update scarfy animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula animation frame
        neb1Data.runningTime += dT;
        if (neb1Data.runningTime>= neb1Data.updateTime)
        {
            neb1Data.runningTime = 0;
            // Update nebula animation frame
            neb1Data.rec.x = neb1Data.frame * neb1Data.rec.width;
            neb1Data.frame++;
            if (neb1Data.frame > 7)
            {
                neb1Data.frame = 0;
            }
        }

        // update second nebula animation frame
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0;
            // Update nebula animation frame
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, neb1Data.rec, neb1Data.pos, WHITE);
        // draw second nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, BLUE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
