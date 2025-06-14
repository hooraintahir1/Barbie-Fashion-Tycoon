#include "play.h"
#include <iostream>
#include "raylib.h"

GamePlay::GamePlay() {
    money = 500.0f;
    score = 0;
    selectionComplete = false;
    showLevelFailed = false;
}

void GamePlay::BuyOutfit(const Outfit& outfit, int level) {
    if (level == 1) {
        inventory.AddOutfit(outfit); 
    }
    else {
        if (money >= outfit.price) {
            money -= outfit.price;
            score += outfit.score;
            inventory.AddOutfit(outfit);
            std::cout << "Bought: " << outfit.name << std::endl;
        }
        else {
            std::cout << "Not enough money for: " << outfit.name << std::endl;
        }
    }
}

void GamePlay::ParticipateInFashionShow(int level) {
    selectionComplete = true;
    if (!CheckLevelComplete(level)) {
        showLevelFailed = true;
    }
}

bool GamePlay::CheckLevelComplete(int level) const {
    if (level == 1) {
        return inventory.Size() == 1;
    }
    else {
        return inventory.Size() == 2; 
    }
}

void GamePlay::DrawStatus(int level) const {
    if (level != 1) {
        DrawText(TextFormat("Money: $%.0f", money), 20, 20, 20, YELLOW);
        DrawText(TextFormat("Score: %d", score), 20, 50, 20, GREEN);
    }
    DrawText(TextFormat("Outfits: %d", inventory.Size()), 20, 80, 20, DARKGREEN);

    if (selectionComplete && showLevelFailed) {
        if (level == 1) {
            if (inventory.Size() != 1)
                DrawText("Level Failed: Pick exactly 1 outfit!", 20, 110, 20, WHITE);
        }
        else {
            if (inventory.Size() < 2)
                DrawText("Level Failed: Pick 2 outfits!", 20, 110, 20, WHITE);
        }
    }
}

float GamePlay::GetMoney() const {
    return money;
}

void GamePlay::ResetForNewLevel(int level) {
    score = 0;
    selectionComplete = false;
    showLevelFailed = false;
    inventory.Clear();
    if (level == 2) money = 800.0f;
}