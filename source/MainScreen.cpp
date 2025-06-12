// ───────────────────────── MainScreen.h ──────────────────────────
#pragma once
#include <raylib.h>
#include <string>
#include <functional>

// Small RAII helpers ---------------------------------------------------------
struct ScopedTexture {
    Texture2D tex{};
    ScopedTexture() = default;
    explicit ScopedTexture(const std::string& file) { tex = LoadTexture(file.c_str()); }
    ScopedTexture(const ScopedTexture&)            = delete;
    ScopedTexture& operator=(const ScopedTexture&) = delete;
    ScopedTexture(ScopedTexture&& other) noexcept  { tex = other.tex; other.tex.id = 0; }
    ~ScopedTexture()                               { if (tex.id) UnloadTexture(tex); }
    operator Texture2D&() { return tex; }
};

struct ScopedSound {
    Sound snd{};
    explicit ScopedSound(const std::string& file) { snd = LoadSound(file.c_str()); }
    ScopedSound(const ScopedSound&)            = delete;
    ScopedSound& operator=(const ScopedSound&) = delete;
    ~ScopedSound()                             { if (snd.frameCount) UnloadSound(snd); }
    operator Sound&() { return snd; }
};

// MainScreen -----------------------------------------------------------------
class MainScreen {
public:
    struct Props {
        std::string backgroundPath = "pink.jpg";
        std::string logoPath       = "barbieLogo.png";
        std::string clickPath      = "click.wav";
        Color      baseBtnColor    = DARKGREEN;
        Color      hoverBtnColor   = GREEN;
        Color      borderColor     = MAGENTA;
        Color      textColor       = DARKPURPLE;
        Vector2    btnSizeRatio    = {0.25f, 0.12f};   // % of window (w,h)
        float      logoHeightRatio = 0.35f;            // % of window height
        int        fontSize        = 30;
    };

    explicit MainScreen(const Props& p = {});
    void   update(float dt);               // animations, hover state
    void   draw() const;                   // render everything
    void   handleClick(Vector2 mouse);     // call from your input code
    bool   shouldStartGame() const { return _startGame; }
    void   reset()                { _startGame = false; _anim = 0.0f; }

private:
    Props        _cfg;
    ScopedTexture _bg, _logo;
    ScopedSound   _click;
    Rectangle     _btn{};                  // recalculated each frame
    bool          _hover      = false;
    bool          _startGame  = false;
    float         _anim       = 0.0f;      // 0 → 1 logo slide‑in
};
MainScreen menu;

void Init()
{
    InitWindow(1280, 720, "My Game");
    InitAudioDevice();
    menu = MainScreen();          // default props, or pass custom
}

void UpdateDrawFrame()
{
    const float dt = GetFrameTime();
    menu.update(dt);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    menu.draw();
    EndDrawing();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        menu.handleClick(GetMousePosition());

    if (menu.shouldStartGame())
        changeToGameplayState();
}
