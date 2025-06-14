#pragma once
#include "outfit.h"
#include "shoes.h"
#include "play.h"
#include "raylib.h"

class GameManager {
public:
    GamePlay session;
    OutfitCatalog catalog;
    Texture2D logo;
    int currentLevel; 

    GameManager() : currentLevel(1) {} 

    void LoadAssets();
    void UnloadAssets();
    void DrawUI();
    void DrawUI(int level); 
    void HandleClick(Vector2 mouse);
    void TryEnterFashionShow();
    void TryEnterFashionShow(int level);
    bool IsLevelComplete() const;
    bool IsLevelComplete(int level) const;
};