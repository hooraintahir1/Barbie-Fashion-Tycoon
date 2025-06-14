#ifndef SCREEN4_H
#define SCREEN4_H

#include "raylib.h"
#include "play.h"
#include "shoes.h"
#include <vector>

class Screen4 {
public:
    Screen4(GamePlay* gameplay, float& moneyRef, int& scoreRef);
    Rectangle finalButton = { 550, 500, 200, 50 }; 
    void Load();
    void Unload();
    void Draw();
    bool ShouldContinue() const;
    std::vector<Shoe> GetSelectedShoes() const;

private:
    GamePlay* game;
    float& money;
    int& score;
    Texture2D levelBackground;
    Texture2D barbieSide;
    std::vector<int> selectedIndices;
    std::vector<Shoe> inventory;
    bool selectionComplete;
};

#endif