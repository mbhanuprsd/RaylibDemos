#include "raylib.h"

int main()
{
    // Window dimensions
    int width = 640, height = 480;
    InitWindow(width, height, "Axe Game");

    // Circle co-ordinates
    int circle_x{width / 4}, circle_y{height / 2};
    int radius = 20;
    // Circle edges
    int l_circle_x{circle_x - radius};
    int r_circle_x{circle_x + radius};
    int u_circle_y{circle_y - radius};
    int b_circle_y{circle_y + radius};

    // Axe co-ordinates
    int axe_x{width / 2}, axe_y{};
    int size = 50;
    int direction{10};
    // Axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + size};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + size};

    bool collision_with_axe = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        if (collision_with_axe)
        {
            DrawText("Game Over!", width / 3, height / 3, 50, RED);
            DrawText("Press Enter to Replay", width / 3, height / 2, 20, GREEN);
            // Reset Game after "Enter" key press
            if (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER))
            {
                circle_x = width / 4;
                circle_y = height / 2;
                axe_x = width / 2, axe_y = 0;
                direction = 10;
                collision_with_axe = false;
            }
        }
        else
        {
            // Game logic starts

            // Update the edges
            l_circle_x = circle_x - radius;
            r_circle_x = circle_x + radius;
            u_circle_y = circle_y - radius;
            b_circle_y = circle_y + radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + size;
            u_axe_y = axe_y;
            b_axe_y = axe_y + size;

            // Check collision
            collision_with_axe =
                (b_axe_y >= u_circle_y) &&
                (u_axe_y <= b_circle_y) &&
                (l_axe_x <= r_circle_x) &&
                (r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, radius, GREEN);

            DrawRectangle(axe_x, axe_y, size, size, RED);

            // Move the axe
            axe_y += direction;
            if (axe_y > (height - size) || axe_y < 0)
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
        }
        EndDrawing();
    }
}