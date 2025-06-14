// shoes.cpp

#include "shoes.h"
#include <iostream>

std::vector<Shoe> ShoeCatalog::shoes;
std::vector<Rectangle> ShoeCatalog::buttons;

void ShoeCatalog::Load() {
    shoes.clear();

    shoes.push_back({ "Casual Shoes",   "Casual",       60,  8,  LoadTexture("casual_shoes.png") });
    shoes.push_back({ "Chic Shoes",     "Chic",         75, 10,  LoadTexture("chic_shoes.png") });
    shoes.push_back({ "Glitter Heels",  "Glitter Gown", 90, 12,  LoadTexture("glitter_heels.png") });
    shoes.push_back({ "Party Heels",    "Party",        80,  9,  LoadTexture("party_heels.png") });
    shoes.push_back({ "Street Shoes",   "Street Style", 65,  7,  LoadTexture("street_shoes.png") });

    buttons.clear();
    for (int i = 0; i < shoes.size(); ++i) {
        float y = 50.0f + i * (buttonHeight + 40.0f);
        buttons.push_back({ 680.0f, y, buttonWidth, buttonHeight });
    }
}

void ShoeCatalog::Unload() {
    for (auto& shoe : shoes) {
        UnloadTexture(shoe.image);
    }
    shoes.clear();
    buttons.clear();
}

void ShoeCatalog::Draw() {
    DrawText("Match 2 shoes:", 550, 20, 20, WHITE);
    buttons.clear();

    for (int i = 0; i < shoes.size(); ++i) {
        float imageX = 500.0f;
        float imageY = 40.0f + i * 100.0f;

        Rectangle src = { 0, 0, (float)shoes[i].image.width, (float)shoes[i].image.height };
        Rectangle dst = { imageX, imageY, 100.0f, 100.0f };

        DrawTexturePro(shoes[i].image, src, dst, { 0, 0 }, 0, WHITE);

        DrawText(TextFormat("$%.0f", shoes[i].price), imageX + 110, imageY + 30, 18, YELLOW);

        buttons.push_back({ imageX, imageY, 100.0f, 100.0f });
    }
}

void ShoeCatalog::HandleClick(Vector2 mouse, float& money, int& score, std::vector<Shoe>& inventory) {
    for (int i = 0; i < buttons.size(); ++i) {
        if (CheckCollisionPointRec(mouse, buttons[i])) {
            const Shoe& selected = shoes[i];

            if (money >= selected.price) {
                money -= selected.price;
                score += selected.score;

                inventory.push_back({
                    selected.name,
                    selected.matchesOutfit,
                    selected.price,
                    selected.score,
                    selected.image
                    });

                std::cout << "Added shoe price: " << selected.price << std::endl;
            }
            else {
                std::cout << "Not enough money for shoe price: " << selected.price << std::endl;
            }
        }
    }
}

const std::vector<Shoe>& ShoeCatalog::GetShoes() {
    return shoes;
}

const std::vector<Rectangle>& ShoeCatalog::GetButtons() {
    return buttons;
}
