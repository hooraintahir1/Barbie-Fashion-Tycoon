#ifndef SHOES_H
#define SHOES_H

#include "raylib.h"
#include <vector>
#include <string>

struct Shoe {
    std::string name;           
    std::string matchesOutfit; 
    float price;
    int score;
    Texture2D image;
};

class ShoeCatalog {
public:
    static void Load();
    static void Unload();
    static void Draw();
    static void HandleClick(Vector2 mouse, float& money, int& score, std::vector<Shoe>& inventory);
    static const std::vector<Shoe>& GetShoes();
    static const std::vector<Rectangle>& GetButtons();
private:
    static std::vector<Shoe> shoes;
    static std::vector<Rectangle> buttons;
    static constexpr float buttonWidth = 100.0f;
    static constexpr float buttonHeight = 40.0f;
};

#endif