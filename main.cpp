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

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // const int width{800};
    // const int height{600};

    WindowSize windowSize{800, 600};

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

    float finishline{ nebulae[sizeOfNebulae - 1].pos.x};

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

    // background x pos
    float bgXPos = 0.0;
    float mgX{};
    float fgX{};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(BLUE);

        bgXPos -= 20 * dT;
        if (bgXPos <= -background.width * 3.5)
        {
            bgXPos = 0.0;
        }

        mgX -= 40 * dT;
        if (mgX <= -midground.width * 3.5)
        {
            mgX = 0;
        }

        fgX -= 80 * dT;
        if (fgX <= -foreground.width * 3.5)
        {
            fgX = 0;
        }

        Vector2 bg1Pos{bgXPos, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 3.5, WHITE);
        float newXPos = bgXPos + background.width * 3.5;
        Vector2 bg2Pos{newXPos, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 3.5, WHITE);

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 3.5, WHITE);
        float mgXPos = mgX + midground.width * 3.5;
        Vector2 mg2Pos{mgXPos, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 3.5, WHITE);

        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 3.5, WHITE);
        float fgXPos = fgX + foreground.width * 3.5;
        Vector2 fg2Pos{fgXPos, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 3.5, WHITE);

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

        // Update scarfy's animation frame
        if (!isInAir)
        {
            scarflyData = updateAnimData(scarflyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);

            nebulae[i].pos.x += nebVel * dT;
        }

        // Update finishline
        finishline += nebVel * dT;

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
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}