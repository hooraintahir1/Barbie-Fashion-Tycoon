#include "play.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

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
            cout << "Bought: " << outfit.name << endl;
        }
        else {
            cout << "Not enough money for: " << outfit.name << endl;
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

void GamePlay::SaveState(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (out) {
        out.write(reinterpret_cast<const char*>(&money), sizeof(money));
        out.write(reinterpret_cast<const char*>(&score), sizeof(score));
       
        size_t count = inventory.GetOutfits().size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& o : inventory.GetOutfits()) {
            size_t len = o.name.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(o.name.c_str(), len);
        }
    }
}

void GamePlay::LoadState(const string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        in.read(reinterpret_cast<char*>(&money), sizeof(money));
        in.read(reinterpret_cast<char*>(&score), sizeof(score));
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        inventory.Clear();
        for (size_t i = 0; i < count; ++i) {
            size_t len;
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            string name(len, '\0');
            in.read(&name[0], len);
            Outfit o;
            o.name = name;
           
            inventory.AddOutfit(o);
        }
    }
}