#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const int width{800};
    const int height{600};

    InitWindow(width, height, "Dapper Dasher!");

    const int rectWidth{50};
    const int rectHeight{80};

    const int gravity{1};
    const int jumpVel{-22};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    Vector2 scarfyPos;


    int posY{height - rectHeight};
    int velocity{0};
    bool isInAir = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(YELLOW);

        if (posY >= height - rectHeight)
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

        posY += velocity;

        DrawRectangle(width / 2, posY, rectWidth, rectHeight, BLUE);

        EndDrawing();
    }
    CloseWindow();
}