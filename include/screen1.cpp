#include "Screen1.h"
#include "raylib.h"

void Screen1::Load() {
    levelBackground = LoadTexture("level.jpg");
    barbieSide = LoadTexture("barbie.png");

    if (levelBackground.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load level.jpg");
    }

    if (barbieSide.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load barbie.png");
    }
}

void Screen1::Unload() {
    UnloadTexture(levelBackground);
    UnloadTexture(barbieSide);
}

void Screen1::Draw() {
    
    Rectangle source = { 0, 0, (float)levelBackground.width, (float)levelBackground.height };
    Rectangle dest = { 0, 0, 800, 600 };
    DrawTexturePro(levelBackground, source, dest, { 0, 0 }, 0.0f, WHITE);

    if (barbieSide.id != 0) {
        // height of barbie
        float desiredWidth = 450.0f;
        float scaleFactor = desiredWidth / barbieSide.width;

        Vector2 barbiePos = { 0.0f, (600.0f - barbieSide.height * scaleFactor) / 2.0f };

        DrawTextureEx(barbieSide, barbiePos, 0.0f, scaleFactor, WHITE);
    }
    else {
        DrawText("Barbie image failed to load!", 50, 50, 20, RED);
    }
}



