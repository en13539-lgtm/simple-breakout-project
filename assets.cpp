#include "assets.h"

#include "raylib.h"

void load_fonts()
{
    menu_font = LoadFontEx("data/fonts/ARCADECLASSIC.TTF", 256, nullptr, 0);
}

void unload_fonts()
{
    UnloadFont(menu_font);
}

void load_textures()
{
    wall_texture = LoadTexture("data/images/wall.png");
    void_texture = LoadTexture("data/images/void.png");
    block_texture = LoadTexture("data/images/block.png");
    paddle_texture = LoadTexture("data/images/paddle.png");
    ball_sprite = load_sprite("data/images/ball/ball", ".png", 8, true, 10);
}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    UnloadTexture(paddle_texture);
    unload_sprite(ball_sprite);
}

void load_sounds()
{
    InitAudioDevice();
    win_sound = LoadSound("data/sounds/win.wav");
    lose_sound = LoadSound("data/sounds/lose.wav");
    cache_sound = LoadSound("data/sounds/cache.mp3");
    bonus_sound = LoadSound("data/sounds/bonus.mp3");
    choice_sound = LoadSound("data/sounds/choice.mp3");
    shopping_music = LoadMusicStream("data/musics/shopping.mp3");
    SetMusicVolume(shopping_music, 0.45f);
    shop_music_loaded = true;
}

void unload_sounds()
{
    UnloadSound(win_sound);
    UnloadSound(lose_sound);
    UnloadSound(cache_sound);
    UnloadSound(bonus_sound);
    UnloadSound(choice_sound);
    if (shop_music_loaded) {
        UnloadMusicStream(shopping_music);
        shop_music_loaded = false;
    }
    CloseAudioDevice();
}
