#include "screen4.h"
#include <algorithm>
#include <iostream>

Screen4::Screen4(GamePlay* gameplay, float& moneyRef, int& scoreRef)
    : game(gameplay), money(moneyRef), score(scoreRef), selectionComplete(false)
{
    Rectangle finalButton;
    finalButton = { 550, 500, 200, 50 };
    selectedIndices.clear();
    inventory.clear();
}

void Screen4::Load() {
    levelBackground = LoadTexture("level.jpg");
    barbieSide = LoadTexture("barbie.png");
    selectedIndices.clear();
    selectionComplete = false;
    inventory.clear();
}

void Screen4::Unload() {
    UnloadTexture(levelBackground);
    UnloadTexture(barbieSide);
}

void Screen4::Draw() {
    ClearBackground(RAYWHITE);
    DrawTexturePro(levelBackground, { 0, 0, (float)levelBackground.width, (float)levelBackground.height },
        { 0, 0, 800, 600 }, { 0, 0 }, 0.0f, WHITE);

    if (barbieSide.id != 0) {
        float scale = 450.0f / barbieSide.width;
        Vector2 pos = { 0, (600 - barbieSide.height * scale) / 2 };
        DrawTextureEx(barbieSide, pos, 0.0f, scale, WHITE);
    }

    DrawText("Match the shoes!", 50, 30, 28, DARKBLUE);
    DrawText(TextFormat("Money: $%.0f  Score: %d", money, score), 50, 70, 20, DARKGREEN);

    ShoeCatalog::Draw();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedIndices.size() < 2) {
        size_t before = inventory.size();
        ShoeCatalog::HandleClick(GetMousePosition(), money, score, inventory);
        if (inventory.size() > before && selectedIndices.size() < 2) {
            selectedIndices.push_back((int)inventory.size() - 1);
        }
    }

    const auto& buttons = ShoeCatalog::GetButtons();
    for (int idx : selectedIndices) {
        if (idx < buttons.size())
            DrawRectangleLines((int)buttons[idx].x, (int)buttons[idx].y, (int)buttons[idx].width, (int)buttons[idx].height, GREEN);
    }

    if (selectedIndices.size() == 2) {
       
        int screenWidth = 800;
        int buttonWidth = 200;
        int buttonHeight = 50;
        int buttonX = (screenWidth - buttonWidth) / 2;
        int buttonY = 500; 

        Rectangle finalButton = { (float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight };

        Color btnColor = DARKGREEN;
        Color textColor = WHITE;
        DrawRectangleRec(finalButton, btnColor);
        DrawRectangleLinesEx(finalButton, 2, WHITE);

        const char* finalText = "Final";
        int finalFontSize = 28;
        int finalTextWidth = MeasureText(finalText, finalFontSize);
        int finalTextX = finalButton.x + (finalButton.width - finalTextWidth) / 2;
        int finalTextY = finalButton.y + (finalButton.height - finalFontSize) / 2;
        DrawText(finalText, (int)finalTextX, (int)finalTextY, finalFontSize, textColor);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, finalButton)) {
                selectionComplete = true;
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            selectionComplete = true;
        }
    }
}

bool Screen4::ShouldContinue() const {
    return selectionComplete;
}

std::vector<Shoe> Screen4::GetSelectedShoes() const {
    std::vector<Shoe> result;
    for (int idx : selectedIndices) {
        if (idx < inventory.size())
            result.push_back(inventory[idx]);
    }
    return result;
}