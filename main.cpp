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

    const int gravity{1'000};
    const int jumpVel{-600};

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec;
    nebulaRec.width = nebula.width / 8;
    nebulaRec.height = nebula.height / 8;
    nebulaRec.x = 0;
    nebulaRec.y = 0;
    Vector2 nebulaPos;
    nebulaPos.x = width;
    nebulaPos.y = height - nebulaRec.height;

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = width / 2 - scarfyRec.width / 2;
    scarfyPos.y = height - scarfyRec.height;

    int velocity{0};
    bool isInAir = false;

    int frame{0};
    const float updateTime{1.0 / 12.0};
    float runningTime{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(YELLOW);

        if (scarfyPos.y >= height - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // Upadate position
        scarfyPos.y += velocity * dT;

        runningTime += dT;
        if (runningTime >= updateTime)
        {
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
            runningTime = 0;
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}