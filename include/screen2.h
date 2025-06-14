#pragma once
#include "play.h"
#include "raylib.h"

class Screen2 {
public:
    Screen2(GamePlay* gameplay, float carryOverMoney);
    void Load();
    void Unload();
    void Draw();
    bool ShouldContinue() const;

private:
    GamePlay* game;
    float moneyEarned;
    Texture2D levelBackground;
    Texture2D barbieSide;
    Rectangle playButton;
};