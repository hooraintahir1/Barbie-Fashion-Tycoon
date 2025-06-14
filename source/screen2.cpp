#include "screen2.h"

Screen2::Screen2(GamePlay* gameplay, float carryOverMoney)
    : playButton{ 530, 500, 180, 50 }, game(gameplay), moneyEarned(carryOverMoney) {
}

void Screen2::Load() {
    levelBackground = LoadTexture("level.jpg");
    barbieSide = LoadTexture("barbie.png");
    game->SetMoney(moneyEarned);
    game->ResetForNewLevel(2);
}
void Screen2::Unload() {
    UnloadTexture(levelBackground);
    UnloadTexture(barbieSide);
}
void Screen2::Draw() {
    Rectangle source = { 0, 0, (float)levelBackground.width, (float)levelBackground.height };
    Rectangle dest = { 0, 0, 800, 600 };
    DrawTexturePro(levelBackground, source, dest, { 0, 0 }, 0.0f, WHITE);

    if (barbieSide.id != 0) {
        float desiredWidth = 450.0f;
        float scaleFactor = desiredWidth / barbieSide.width;
        Vector2 barbiePos = { 0.0f, (600.0f - barbieSide.height * scaleFactor) / 2.0f };
        DrawTextureEx(barbieSide, barbiePos, 0.0f, scaleFactor, WHITE);
    }
    else {
        DrawText("Barbie image failed to load!", 50, 50, 20, RED);
    }

    int baseX = 480;
    int y = 70;

    DrawText("Level 2 Begins!", baseX, y, 30, PINK);
    y += 50;
    DrawText(TextFormat("Total Money: $%.0f", moneyEarned), baseX, y, 25, YELLOW);
    y += 40;
    DrawText("Pick 2 outfits.", baseX, y, 20, GREEN);
    y += 340;

    Color btnColor = DARKGREEN;
    Color textColor = WHITE;
    DrawRectangleRec(playButton, btnColor);
    DrawRectangleLinesEx(playButton, 2, WHITE);

    const char* playText = "Play";
    int playFontSize = 28;
    int playTextWidth = MeasureText(playText, playFontSize);
    int playTextX = playButton.x + (playButton.width - playTextWidth) / 2;
    int playTextY = playButton.y + (playButton.height - playFontSize) / 2;
    DrawText(playText, playTextX, playTextY, playFontSize, textColor);
}

bool Screen2::ShouldContinue() const {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, playButton)) {
            return true;
        }
    }
    return false;
}