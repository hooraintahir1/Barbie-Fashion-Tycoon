#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include "raylib.h"

class MainScreen {
private:
    Texture2D logo;
    Sound clickSound;
    Rectangle playButton;
    bool startGame;

public:
    MainScreen();
    ~MainScreen();

    Texture2D background;
    void Load();
    void Unload();
    void Draw();
    void HandleClick(Vector2 mouse);
    bool ShouldStartGame() const;
    void SetBackground(Texture2D bg);
};

#endif
