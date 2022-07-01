#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

struct WindowSize
{
    int width;
    int height;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

int main()
{
    // const int width{800};
    // const int height{600};

    WindowSize windowSize{1200, 600};

    InitWindow(windowSize.width, windowSize.height, "Dapper Dasher!");

    const int gravity{1'000};
    const int jumpVel{-600};

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Using arrary to store nebula hazards
    AnimData nebulae[25]{};
    const int sizeOfNebulae{25};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8.0;
        nebulae[i].rec.height = nebula.height / 8.0;
        nebulae[i].pos.y = windowSize.height - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;

        nebulae[i].pos.x = windowSize.width + i * 300;
    }

    int nebVel{-200};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarflyData;
    scarflyData.rec.width = scarfy.width / 6;
    scarflyData.rec.height = scarfy.height;
    scarflyData.rec.x = 0;
    scarflyData.rec.y = 0;
    scarflyData.pos.x = windowSize.width / 2 - scarflyData.rec.width / 2;
    scarflyData.pos.y = windowSize.height - scarflyData.rec.height;
    scarflyData.frame = 0;
    scarflyData.updateTime = 1.0 / 12.0;
    scarflyData.runningTime = 0.0;

    int velocity{0};
    bool isInAir = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(BLUE);

        // Update scarfy position
        if (isOnGround(scarflyData, windowSize.height))
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
        scarflyData.pos.y += velocity * dT;

        if (!isInAir)
        {
            scarflyData.runningTime += dT;
            if (scarflyData.runningTime >= scarflyData.updateTime)
            {
                scarflyData.rec.x = scarflyData.frame * scarflyData.rec.width;
                scarflyData.frame++;
                if (scarflyData.frame > 5)
                {
                    scarflyData.frame = 0;
                }
                scarflyData.runningTime = 0;
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Nebula update frames
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
                nebulae[i].runningTime = 0;
            }

            nebulae[i].pos.x += nebVel * dT;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw scarfy
        DrawTextureRec(scarfy, scarflyData.rec, scarflyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}