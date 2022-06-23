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
    Rectangle nebRec;
    nebRec.x = 0;
    nebRec.y = 0;
    nebRec.width = nebula.width / 8.0f;
    nebRec.height = nebula.height / 8.0f;
    Vector2 nebPos{width, height - nebRec.height};

    Rectangle neb2Rec;
    neb2Rec.x = 0;
    neb2Rec.y = 0;
    neb2Rec.width = nebula.width / 8.0f;
    neb2Rec.height = nebula.height / 8.0f;
    Vector2 neb2Pos{width + 300, height - nebRec.height};

    // nebulat x velocity pixels per second
    int nebVel{-200};

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

    // Scarfy animation
    int frame{0};
    const float updateTime{1.0 / 12.0};
    float runningTime{0};

    // Nebula animation
    int nebFrame{0};
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{0};

    int neb2Frame{0};
    const float neb2UpdateTime{1.0 / 16.0};
    float neb2RunningTime{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(BLUE);

        // Upadate nebula postion
        nebPos.x += nebVel * dT;
        neb2Pos.x += nebVel * dT;

        // Update scarfy position
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

        if (!isInAir)
        {
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
        }

        // Nebula update frames
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
            nebRunningTime = 0;
        }

        // Nebula2 update frames
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
            neb2RunningTime = 0;
        }

        // Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // Draw 2nd nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}