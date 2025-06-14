// outfit.cpp

#include "outfit.h"
#include <iostream>

void OutfitCatalog::Load() {
    outfits.push_back({ "Casual", 100, 10, LoadTexture("casual.png"), "Cool" });
    outfits.push_back({ "Chic", 200, 12, LoadTexture("chic.png"), "Trendsetter" });
    outfits.push_back({ "Glitter Gown", 250, 20, LoadTexture("glitter_gown.png"), "Romantic" });
    outfits.push_back({ "Party", 300, 15, LoadTexture("party.png"), "Entertaining" });
    outfits.push_back({ "Street Style", 120, 8, LoadTexture("street_style.png"), "Adventurer" });

    buttons.clear();
    for (int i = 0; i < outfits.size(); ++i) {
        float y = 50.0f + i * (buttonHeight + 40.0f);
        buttons.push_back({ 680.0f, y, buttonWidth, buttonHeight });
    }
}

void OutfitCatalog::Unload() {
    for (auto& outfit : outfits) {
        UnloadTexture(outfit.image);
    }
    outfits.clear();
    buttons.clear();
}

// Draw outfits and their buttons on the screen
void OutfitCatalog::Draw(int level) {
    if (level = 1) {
        DrawText("Click an outfit:", 550, 20, 20, WHITE);
    }
    else {
        DrawText("Select 2 outfits:", 550, 20, 20, WHITE);
    }

    buttons.clear();  // Recalculate buttons each draw

    for (int i = 0; i < outfits.size(); ++i) {
        float imageX = 500.0f;
        float imageY = 40.0f + i * 100.0f;

        Rectangle src = { 0, 0, (float)outfits[i].image.width, (float)outfits[i].image.height };
        Rectangle dst = { imageX, imageY, 100.0f, 100.0f };

        DrawTexturePro(outfits[i].image, src, dst, { 0, 0 }, 0, WHITE);
        DrawText(outfits[i].name.c_str(), imageX + 110, imageY + 20, 16, GREEN);

        if (level != 1) {
            DrawText(TextFormat("$%.0f", outfits[i].price), imageX + 110, imageY + 40, 16, WHITE);
        }

        buttons.push_back({ imageX, imageY, 100.0f, 100.0f });
    }
}

// Utility to trim whitespace from outfit names
std::string Trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Handle mouse click: buy outfit if allowed
void OutfitCatalog::HandleClick(Vector2 mouse, float& money, int& score, std::vector<Outfit>& inventory, int level) {
    for (int i = 0; i < buttons.size(); ++i) {
        if (CheckCollisionPointRec(mouse, buttons[i])) {
            const Outfit& clicked = outfits[i];

            bool canBuy = (level == 1 || money >= clicked.price);

            if (canBuy) {
                if (level != 1) {
                    money -= clicked.price;
                }

                score += clicked.score;

                // Copy the outfit but reuse the loaded texture
                Outfit purchased = {
                    Trim(clicked.name),
                    clicked.price,
                    clicked.score,
                    clicked.image,
                    clicked.personalityType
                };

                inventory.push_back(purchased);

                std::cout << "Added to inventory: " << purchased.name << std::endl;
            }
            else {
                std::cout << "Not enough money for: " << clicked.name << std::endl;
            }
        }
    }
}

// Accessors
const std::vector<Outfit>& OutfitCatalog::GetOutfits() const {
    return outfits;
}

const std::vector<Rectangle>& OutfitCatalog::GetButtons() const {
    return buttons;
}
