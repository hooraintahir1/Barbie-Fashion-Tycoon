#include "finalfashionshow.h"
#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void RunFinalFashionShow(GamePlay& game, const std::vector<Outfit>& outfits, const std::vector<Shoe>& shoes, int level) {
    
    Texture2D background = LoadTexture("fashionShow.jpg");
    Music bgm = LoadMusicStream("background.wav");
    Music levelupMusic = LoadMusicStream("levelup.wav");
    PlayMusicStream(bgm);

    std::map<std::string, std::pair<std::string, float>> goodRemarks = {
        {"Casual",        {"Perfect casual match! The judges are delighted!", 40}},
        {"Chic",          {"Chic and coordinated! Superb!", 50}},
        {"Glitter Gown",  {"Glamour overload! The crowd goes wild!", 60}},
        {"Party",         {"Party queen! Unbeatable style!", 45}},
        {"Street Style",  {"Urban edge, perfectly synced!", 55}}
    };

    std::string badRemark = "Mismatch! Judges are not impressed.";

    int totalPairs = std::min(outfits.size(), shoes.size());
    int currentPair = 0;
    int frameCounter = 0;

    bool showComplete = false;
    bool canAdvance = false;
    bool floatScoresActive = false;

    std::vector<ScoreFloat> floatingScores;

    std::srand((unsigned int)time(nullptr)); 

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        BeginDrawing();

        // Draw background
        DrawTexturePro(background, { 0, 0, (float)background.width, (float)background.height }, { 0, 0, 800, 600 }, { 0, 0 }, 0.0f, WHITE);

        if (currentPair < totalPairs) {
            const Outfit& outfit = outfits[currentPair];
            const Shoe& shoe = shoes[currentPair];
            bool match = (outfit.name == shoe.matchesOutfit);

            std::string remark = badRemark;
            float bonus = 0;

            if (match && goodRemarks.count(outfit.name)) {
                remark = goodRemarks[outfit.name].first;
                bonus = goodRemarks[outfit.name].second;
            }

            DrawText(TextFormat("Outfit: %s", outfit.name.c_str()), 50, 30, 28, DARKGREEN);
            DrawText(TextFormat("Shoe (matches): %s", shoe.matchesOutfit.c_str()), 50, 70, 22, DARKBLUE);
            DrawText(TextFormat("Judges: %s", remark.c_str()), 50, 110, 22, match ? YELLOW : WHITE);

            if (level != 1)
                DrawText(TextFormat("Bonus Money: $%.0f", bonus), 50, 150, 22, match ? YELLOW : WHITE);

            DrawText("Press SPACE for next pair...", 50, 500, 20, WHITE);

            // Display outfit image
            if (outfit.image.id) {
                DrawTexturePro(outfit.image, { 0, 0, (float)outfit.image.width, (float)outfit.image.height }, { 80, 200, 260, 260 }, { 0, 0 }, 0.0f, WHITE);
            }

            // Display shoe image
            if (shoe.image.id) {
                DrawTexturePro(shoe.image, { 0, 0, (float)shoe.image.width, (float)shoe.image.height }, { 380, 250, 180, 180 }, { 0, 0 }, 0.0f, WHITE);
            }

            // Show floating score visuals in Level 2+
            if (level != 1) {
                if (!floatScoresActive) {
                    floatingScores.clear();
                    int baseX = 240, gap = 120;

                    if (match) {

                        floatingScores.push_back({ 10, (float)(baseX + 0 * gap), 650, GREEN });
                        floatingScores.push_back({ 10, (float)(baseX + 1 * gap), 650, YELLOW });
                        floatingScores.push_back({ 10, (float)(baseX + 2 * gap), 650, PINK });
                    }
                    else {
                     
                        floatingScores.push_back({ 2 + rand() % 3, (float)(baseX + 0 * gap), 650, RED });
                        floatingScores.push_back({ 3 + rand() % 3, (float)(baseX + 1 * gap), 650, ORANGE });
                        floatingScores.push_back({ 2 + rand() % 3, (float)(baseX + 2 * gap), 650, SKYBLUE });
                    }

                    floatScoresActive = true;
                }

                for (auto& f : floatingScores) {
                    DrawText(TextFormat("%d", f.value), f.x, f.y, 60, f.color);
                    f.y -= 3.0f;
                }

                bool offScreen = true;
                for (auto& f : floatingScores) {
                    if (f.y > 300) offScreen = false;
                }

                frameCounter++;
                if (frameCounter > 30) canAdvance = true;

                if (IsKeyPressed(KEY_SPACE) && canAdvance && offScreen) {
                    if (bonus > 0) game.AddMoney(bonus);

                    currentPair++;
                    frameCounter = 0;
                    canAdvance = false;
                    floatScoresActive = false;
                }
            }
            else {
               
                if (IsKeyPressed(KEY_SPACE)) {
                    currentPair++;
                }
            }
        }
        else {
          
            if (!showComplete) {
                StopMusicStream(bgm);
                PlayMusicStream(levelupMusic);
                showComplete = true;
            }

            UpdateMusicStream(levelupMusic);
            DrawText("Final Fashion Show Complete!", 170, 200, 38, GOLD);
            DrawText("Press ESC to return...", 250, 270, 22, WHITE);

            if (IsKeyPressed(KEY_ESCAPE)) {
                break;
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
