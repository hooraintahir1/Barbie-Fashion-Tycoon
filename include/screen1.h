#ifndef SCREEN1_H
#define SCREEN1_H

#include "raylib.h"

struct Screen1 {
    Texture2D levelBackground;
    Texture2D barbieSide;

    void Load();
    void Unload();
    void Draw();
};

#endif
