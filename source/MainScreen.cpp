#include "MainScreen.h"

MainScreen::MainScreen() {
    startGame = false;
}

MainScreen::~MainScreen() {
}

void MainScreen::Load() {
    logo = LoadTexture("barbieLogo.png");
    background = LoadTexture("pink.jpg");
    clickSound = LoadSound("click.wav");
    playButton = { 300, 300, 200, 60 };
    startGame = false;
}

void MainScreen::Unload() {
    UnloadTexture(logo);
    UnloadTexture(background);
    UnloadSound(clickSound);
}

void MainScreen::Draw() {
    Rectangle source = { 0, 0, (float)background.width, (float)background.height };
    Rectangle dest = { 0, 0, 800, 600 };
    DrawTexturePro(background, source, dest, { 0, 0 }, 0.0f, WHITE);

    float targetHeight = 250.0f;
    float scale = targetHeight / logo.height;
    float logoWidthScaled = logo.width * scale;

    float logoX = playButton.x + (playButton.width - logoWidthScaled) / 2;
    float logoY = playButton.y - targetHeight - 20;

    DrawTextureEx(logo, { logoX, logoY }, 0.0f, scale, WHITE);

    Color btnColor = DARKGREEN;
    Color textColor = DARKPURPLE;

    DrawRectangleRec(playButton, btnColor);
    DrawRectangleLinesEx(playButton, 2, MAGENTA);

    const char* text = "Play";
    int fontSize = 30;
    int textWidth = MeasureText(text, fontSize);
    int textX = playButton.x + (playButton.width - textWidth) / 2;
    int textY = playButton.y + (playButton.height - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, textColor);
}

void MainScreen::HandleClick(Vector2 mouse) {
    if (CheckCollisionPointRec(mouse, playButton)) {
        PlaySound(clickSound);
        startGame = true;
    }
}

bool MainScreen::ShouldStartGame() const {
    return startGame;
}

void MainScreen::SetBackground(Texture2D bg) {
    background = bg;
}
