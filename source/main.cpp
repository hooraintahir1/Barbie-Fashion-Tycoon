#include "raylib.h"
#include "MainScreen.h"
#include "Screen1.h"
#include "outfit.h"
#include "play.h"
#include "fashionShow.h"
#include "screen2.h"
#include "screen4.h"
#include "shoes.h"
#include "GameManager.h"
#include "finalfashionshow.h" 
#include <vector>
#include <string>
#include <iostream>

int main() {
    InitWindow(800, 600, "Barbie Fashion Tycoon");
    InitAudioDevice();
    SetTargetFPS(60);

    enum GameState { SPLASH, LEVEL_1, SCREEN_2, LEVEL_2, SCREEN_4, FINAL_SHOW };
    GameState state = SPLASH;

    Texture2D background = LoadTexture("pink.jpg");
    Music bgm = LoadMusicStream("background.wav");
    PlayMusicStream(bgm);

    MainScreen splash;
    splash.Load();
    splash.background = background;

    GameManager game;
    Screen1 level1;
    Screen2* level2Screen = nullptr;
    Screen1* level2 = nullptr;
    Screen4* screen4 = nullptr;

    Rectangle finalButton = { 300, 500, 200, 50 };
    Rectangle nextButton = { 300, 500, 200, 50 };

    ShoeCatalog::Load();

    float& money = game.session.money;
    int& score = game.session.score;

    bool waitForKeyRelease = false;

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Rectangle source = { 0, 0, (float)background.width, (float)background.height };
        Rectangle dest = { 0, 0, 800, 600 };
        DrawTexturePro(background, source, dest, { 0, 0 }, 0.0f, WHITE);

        switch (state) {
        case SPLASH:
            splash.Draw();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                splash.HandleClick(GetMousePosition());
                if (splash.ShouldStartGame()) {
                    game.LoadAssets();
                    level1.Load();
                    game.currentLevel = 1; 
                    state = LEVEL_1;
                }
            }
            break;

        case LEVEL_1: {
            level1.Draw();
            game.DrawUI();
     
            bool canEnterShow = (game.session.GetInventory().Size() == 1);
            Color btnColor = canEnterShow ? DARKGREEN : GRAY;
            Color textColor = WHITE;
            DrawRectangleRec(finalButton, btnColor);
            DrawRectangleLinesEx(finalButton, 2, WHITE);
            const char* finalText = "Reveal";
            int finalFontSize = 28;
            int finalTextWidth = MeasureText(finalText, finalFontSize);
            int finalTextX = finalButton.x + (finalButton.width - finalTextWidth) / 2;
            int finalTextY = finalButton.y + (finalButton.height - finalFontSize) / 2;
            DrawText(finalText, finalTextX, finalTextY, finalFontSize, textColor);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                game.HandleClick(mouse);

                if (canEnterShow && CheckCollisionPointRec(mouse, finalButton)) {
                    game.TryEnterFashionShow();

                    level2Screen = new Screen2(&game.session, 800.0f);
                    level2Screen->Load();
                    state = SCREEN_2;
                }
            }
            break;
        }

        case SCREEN_2:
            level2Screen->Draw();
            if (level2Screen->ShouldContinue()) {
                delete level2Screen;
                level2Screen = nullptr;

                level2 = new Screen1();
                level2->Load();
                game.currentLevel = 2; 
                state = LEVEL_2;
            }
            break;

        case LEVEL_2: {
            level2->Draw();
            game.DrawUI(); 

            Color btnColor = (game.session.GetInventory().Size() == 2) ? DARKGREEN : GRAY;
            Color textColor = WHITE;
            DrawRectangleRec(nextButton, btnColor);
            DrawRectangleLinesEx(nextButton, 2, WHITE);
            const char* nextText = "Next";
            int nextFontSize = 28;
            int nextTextWidth = MeasureText(nextText, nextFontSize);
            int nextTextX = nextButton.x + (nextButton.width - nextTextWidth) / 2;
            int nextTextY = nextButton.y + (nextButton.height - nextFontSize) / 2;
            DrawText(nextText, nextTextX, nextTextY, nextFontSize, textColor);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (game.session.GetInventory().Size() < 2) {
                    game.HandleClick(mouse);
                }
                if (game.session.GetInventory().Size() == 2 && CheckCollisionPointRec(mouse, nextButton)) {
                    if (screen4) { screen4->Unload(); delete screen4; }
                    screen4 = new Screen4(&game.session, money, score);
                    screen4->Load();
                    state = SCREEN_4;
                    waitForKeyRelease = true;
                }
            }
            break;
        }

        case SCREEN_4:
            if (waitForKeyRelease) {
                if (!IsKeyDown(KEY_SPACE) && !IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    waitForKeyRelease = false;
                }
            }
            else {
                if (screen4) screen4->Draw();

                if (screen4 && screen4->ShouldContinue()) {
                    std::vector<Outfit> selectedOutfits = game.session.GetInventory().GetOutfits();
                    std::vector<Shoe> selectedShoes = screen4->GetSelectedShoes();

                    screen4->Unload();
                    delete screen4;
                    screen4 = nullptr;

                    RunFinalFashionShow(game.session, selectedOutfits, selectedShoes, game.currentLevel);

                    state = SPLASH; 
                }
            }
            break;
        }

        EndDrawing();
    }

    if (state != SPLASH) {
        game.UnloadAssets();
        level1.Unload();
        if (level2) { level2->Unload(); delete level2; }
        if (level2Screen) { level2Screen->Unload(); delete level2Screen; }
        if (screen4) { screen4->Unload(); delete screen4; }
    }

    splash.Unload();
    UnloadTexture(background);
    UnloadMusicStream(bgm);
    ShoeCatalog::Unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}