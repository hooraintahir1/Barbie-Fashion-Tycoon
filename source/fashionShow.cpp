#include "fashionShow.h"
#include "outfit.h"
#include "raylib.h"
#include "play.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

void RunFashionShow(GamePlay& game) {
    Texture2D background = LoadTexture("fashionShow.jpg");
    Music bgm = LoadMusicStream("background.wav");
    Music levelupMusic = LoadMusicStream("levelup.wav");
    PlayMusicStream(bgm);

    std::map<std::string, std::string> personalityDescriptions = {
        {"Adventurer", "You love to try new trends and stand out from the crowd!"},
        {"Romantic", "Soft colors and elegant touches define your style."},
        {"Trendsetter", "You're always ahead of the curve and inspire others!"},
        {"Entertaining", "You bring energy and sparkle to every room."},
        {"Cool", "You value comfort but never compromise on style."}
    };

    const std::vector<Outfit>& wornOutfits = game.GetInventory().GetOutfits();

    int totalOutfits = wornOutfits.size();
    bool showComplete = false;
    bool canAdvance = false;
    int frameCounter = 0;
    int currentOutfit = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        BeginDrawing();

        Rectangle src = { 0, 0, (float)background.width, (float)background.height };
        Rectangle dst = { 0, 0, 800, 600 };
        DrawTexturePro(background, src, dst, { 0, 0 }, 0.0f, WHITE);

        if (currentOutfit < totalOutfits) {
            const Outfit& outfit = wornOutfits[currentOutfit];

           
            std::string personality = outfit.personalityType;
            std::string description = personalityDescriptions.count(personality)
                ? personalityDescriptions[personality]
                : "Unique fashion spirit!";
           
            DrawText("Personality:", 50, 30, 30, PINK);
            DrawText(personality.c_str(), 220, 70, 30, YELLOW);
            DrawText(description.c_str(), 50, 110, 24, WHITE); 

            Rectangle osrc = { 0, 0, (float)outfit.image.width, (float)outfit.image.height };
            float targetWidth = 350;
            float targetHeight = 350;
            float centerX = (800 - targetWidth) / 2.0f;
            float centerY = (600 - targetHeight) / 2.0f;
            Rectangle odst = { centerX, centerY, targetWidth, targetHeight };
            DrawTexturePro(outfit.image, osrc, odst, { 0, 0 }, 0.0f, WHITE);

            DrawText("Press SPACE for next outfit...", 50, 500, 20, GRAY);

            frameCounter++;
            if (frameCounter > 30) canAdvance = true;
            if (IsKeyPressed(KEY_SPACE) && canAdvance) {
                currentOutfit++;
                frameCounter = 0;
                canAdvance = false;
            }
        }
        else {
            if (!showComplete) {
                StopMusicStream(bgm);
                PlayMusicStream(levelupMusic);
                showComplete = true;
            }

            UpdateMusicStream(levelupMusic);
            DrawText("Level 1 Complete!", 250, 200, 40, GOLD);
            float btnWidth = 220;
            float btnHeight = 60;
            float btnX = (800 - btnWidth) / 2.0f;
            float btnY = 330;
            Rectangle nextLevelButton = { btnX, btnY, btnWidth, btnHeight };

            Color btnColor = DARKGREEN;
            Color textColor = WHITE;
            DrawRectangleRec(nextLevelButton, btnColor);
            DrawRectangleLinesEx(nextLevelButton, 3, GOLD);

            const char* btnText = "Next Level";
            int fontSize = 28;
            int textWidth = MeasureText(btnText, fontSize);
            int textX = nextLevelButton.x + (nextLevelButton.width - textWidth) / 2;
            int textY = nextLevelButton.y + (nextLevelButton.height - fontSize) / 2;
            DrawText(btnText, (int)textX, (int)textY, fontSize, textColor);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, nextLevelButton)) {
                    break;
                }
            }
        }

        EndDrawing();
    }

    StopMusicStream(bgm);
    StopMusicStream(levelupMusic);
    UnloadMusicStream(bgm);
    UnloadMusicStream(levelupMusic);
    UnloadTexture(background);
}