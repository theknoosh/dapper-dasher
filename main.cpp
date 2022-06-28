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
        nebData.pos.x += nebVel * dT;
        neb2Data.pos.x += nebVel * dT;

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
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
            nebData.runningTime = 0;
        }

        // Nebula2 update frames
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
            neb2Data.runningTime = 0;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // Draw 2nd nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // Draw scarfy
        DrawTextureRec(scarfy, scarflyData.rec, scarflyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}