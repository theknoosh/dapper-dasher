#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int width{800};
    const int height{600};

    InitWindow(width, height, "Dapper Dasher!");

    // const int rectWidth{50};
    // const int rectHeight{80};

    const int gravity{1};
    const int jumpVel{-22};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = width / 2 - scarfyRec.width / 2;
    scarfyPos.y = height - scarfyRec.height;

    // int posY{height - rectHeight};
    int velocity{0};
    bool isInAir = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(YELLOW);

        if (scarfyPos.y >= height - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // posY += velocity;
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}