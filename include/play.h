#pragma once
#include "outfit.h"
#include "inventory.h"
using namespace std;

class GamePlay {
public:
    float money;
    int score;
    void AddMoney(float m) { money += m; }
    bool selectionComplete;
    bool showLevelFailed;
    Inventory inventory;

    GamePlay();

    void BuyOutfit(const Outfit& outfit, int level);
    void ParticipateInFashionShow(int level);
    bool CheckLevelComplete(int level) const;
    void DrawStatus(int level) const;
    float GetMoney() const;
    void SetMoney(float m) { money = m; }
    void ResetForNewLevel(int level);
    Inventory& GetInventory() { return inventory; }
    
    void SaveState(const string& filename) const;
    void LoadState(const string& filename);
};