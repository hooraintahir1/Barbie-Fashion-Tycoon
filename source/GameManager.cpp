#include "GameManager.h"
#include <vector>
#include <string>
#include "fashionShow.h"
#include "raylib.h"

void GameManager::LoadAssets() {
    logo = LoadTexture("barbieLogo.png");
    catalog.Load();

}

void GameManager::UnloadAssets() {
    UnloadTexture(logo);
    catalog.Unload();
}

void GameManager::DrawUI() {
    DrawUI(currentLevel);
}

void GameManager::DrawUI(int level) {
    DrawTexture(logo, 600, 20, WHITE);
    session.DrawStatus(level); 
    catalog.Draw(currentLevel);
}

void GameManager::HandleClick(Vector2 mouse) {
    const std::vector<Outfit>& options = catalog.GetOutfits();
    const std::vector<Rectangle>& buttons = catalog.GetButtons();

    for (int i = 0; i < buttons.size(); ++i) {
        if (CheckCollisionPointRec(mouse, buttons[i])) {
            session.BuyOutfit(options[i], currentLevel); 
        }
    }
}

void GameManager::TryEnterFashionShow() {
    TryEnterFashionShow(currentLevel);
}

void GameManager::TryEnterFashionShow(int level) {
    session.ParticipateInFashionShow(level); 
    if (!session.showLevelFailed) {
        RunFashionShow(session);
    }
}

bool GameManager::IsLevelComplete() const {
    return IsLevelComplete(currentLevel);
}

bool GameManager::IsLevelComplete(int level) const {
    return session.selectionComplete && !session.showLevelFailed && session.CheckLevelComplete(level);
}