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

int main()
{
    // const int width{800};
    // const int height{600};

    WindowSize windowSize{800, 600};

    InitWindow(windowSize.width, windowSize.height, "Dapper Dasher!");

    const int gravity{1'000};
    const int jumpVel{-600};

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData{
        {0.0, 0.0, static_cast<float>(nebula.width / 8.0), nebula.height / 8.0f},                          // Rectangle rec
        {static_cast<float>(windowSize.width), static_cast<float>(windowSize.height - nebula.height / 8)}, // Vector2 pos
        0,                                                                                                 // int frame
        1.0 / 12.0,                                                                                        // float updateTime
        0.0                                                                                                // float runningTime
    };

    // AnimData for neb2
    AnimData neb2Data{
        {0.0, 0.0, static_cast<float>(nebula.width / 8.0), nebula.height / 8.0f},                                // Rectangle rec
        {static_cast<float>(windowSize.width + 300), static_cast<float>(windowSize.height - nebula.height / 8)}, // Vector2 pos
        0,                                                                                                       // int frame
        1.0 / 16.0,                                                                                              // float updateTime
        0.0                                                                                                      // float runningTime
    };

    // Using arrary to store nebula hazards
    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8.0;
        nebulae[i].rec.height = nebula.height / 8.0;
        nebulae[i].pos.y = windowSize.height - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowSize.width;
    nebulae[1].pos.x = windowSize.width + 300;
    nebulae[2].pos.x = windowSize.width + 600;

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

    // Scarfy animation
    // const float updateTime{1.0 / 12.0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(BLUE);

        // Upadate nebula postion
        nebulae[0].pos.x += nebVel * dT;
        nebulae[1].pos.x += nebVel * dT;

        // Update scarfy position
        if (scarflyData.pos.y >= windowSize.height - scarflyData.rec.height)
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

        // Nebula update frames
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
            nebulae[0].runningTime = 0;
        }

        // Nebula2 update frames
        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
            nebulae[1].runningTime = 0;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // Draw 2nd nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        // Draw scarfy
        DrawTextureRec(scarfy, scarflyData.rec, scarflyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}