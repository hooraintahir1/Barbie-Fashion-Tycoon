
#ifndef OUTFIT_H
#define OUTFIT_H

#include "raylib.h"
#include <string>
#include <vector>

struct Outfit {
    std::string name;
    float price;
    int score;
    Texture2D image;
    std::string personalityType;
};

class OutfitCatalog {
private:
    std::vector<Outfit> outfits;
    std::vector<Rectangle> buttons;
    const float buttonWidth = 100.0f;
    const float buttonHeight = 100.0f;
    const float margin = 20.0f;

public:
    void Load();
    void Unload();
    void Draw(int level);
    void HandleClick(Vector2 mouse, float& money, int& score, std::vector<Outfit>& inventory, int level);
    const std::vector<Outfit>& GetOutfits() const;
    const std::vector<Rectangle>& GetButtons() const;

};

#endif 
