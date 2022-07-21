#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrameCount)
{
    // update animation frame
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrameCount - 1)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // Window dimensions
    const int windowDimensions[2] = {640, 480};

    // Initialize th windows
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    const int gravity{1000}; // Gravity - (pixels/s)/s

    // Scarfy's parameters
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0, 0, scarfy.width / 6, scarfy.height},
        {windowDimensions[0] / 2 - scarfy.width / 12, windowDimensions[1] - scarfy.height},
        0,
        1.0 / 12.0,
        0.0};

    int velocity{};
    const int jumpVel{-600}; // Velocity - pixel/s
    bool isInAir{};

    // Nebula's parameters
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int nebulaeSize{6};
    AnimData nebulae[nebulaeSize];
    for (int i = 0; i < nebulaeSize; i++)
    {
        nebulae[i].rec.x = 0;
        nebulae[i].rec.y = 0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = windowDimensions[0] + i * 400;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
        nebulae[i].updateTime = 1.0 / 12.0;
    }
    const int nebVel{-300}; // Velocity - pixel/s

    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()}; // Delta time

        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check for scarfy
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // Rectangle is on ground
            velocity = 0;
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 6);
        }

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Loop for nebulae
        for (int i = 0; i < nebulaeSize; i++)
        {
            // update nebula position
            nebulae[i].pos.x += nebVel * dT;

            nebulae[i] = updateAnimData(nebulae[i], dT, 8);

            // draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
