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
    const int windowDimensions[2] = {500, 320};
    const int groundScale = windowDimensions[0]/150;

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
        nebulae[i].pos.x = windowDimensions[0] + i * 150 * groundScale;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
        nebulae[i].updateTime = 1.0 / 12.0;
    }
    float finishLine{nebulae[nebulaeSize - 1].pos.x};

    const int nebVel{-300}; // Velocity - pixel/s

    // Background setup
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};


    bool collision{};

    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()}; // Delta time

        BeginDrawing();
        ClearBackground(WHITE);

        // Update background
        bgX -= 20 * dT;
        if (bgX <= -background.width * groundScale)
        {
            bgX = 0;
        }
        // Draw background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, groundScale, WHITE);
        Vector2 bg2Pos{bgX + background.width * groundScale, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, groundScale, WHITE);

        // Update midground
        mgX -= 40 * dT;
        if (mgX <= -midground.width * groundScale)
        {
            mgX = 0;
        }
        // Draw midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, groundScale, WHITE);
        Vector2 mg2Pos{mgX + midground.width * groundScale, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, groundScale, WHITE);

        // Update foreground
        fgX -= 80 * dT;
        if (fgX <= -foreground.width * groundScale)
        {
            fgX = 0;
        }
        // Draw foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, groundScale, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * groundScale, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, groundScale, WHITE);

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

        // Loop for nebulae
        for (int i = 0; i < nebulaeSize; i++)
        {
            // update nebula position
            nebulae[i].pos.x += nebVel * dT;

            nebulae[i] = updateAnimData(nebulae[i], dT, 8);
        }
        // update finishline
        finishLine += nebVel * dT;

        // Check collision
        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            DrawText("Game Over!!", windowDimensions[0]/4, windowDimensions[1]/2, 15*groundScale, RED);
        }
        else if (scarfyData.pos.x > finishLine)
        {
            DrawText("You Won!!!", windowDimensions[0]/4, windowDimensions[1]/2, 15*groundScale, GREEN);
        }
        else
        {
            for (int i = 0; i < nebulaeSize; i++)
            {
                // draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}
