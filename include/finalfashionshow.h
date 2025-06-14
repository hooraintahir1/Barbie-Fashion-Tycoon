#ifndef FINALFASHIONSHOW_H
#define FINALFASHIONSHOW_H

#include "play.h"
#include "outfit.h"
#include "shoes.h"
#include <vector>
#include "raylib.h"

struct ScoreFloat {
    int value;
    float x, y;
    Color color;
};

void RunFinalFashionShow(GamePlay& game, const std::vector<Outfit>& outfits, const std::vector<Shoe>& shoes, int level);

#endif