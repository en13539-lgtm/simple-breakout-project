#include "assets.h"
#include "ball.h"
#include "game.h"
#include "graphics.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

void update()
{
    if (shop_music_loaded) {
        UpdateMusicStream(shopping_music);
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (game_state == in_game_state) game_state = paused_state;
        else if (game_state == paused_state) game_state = in_game_state;
    }
    switch (game_state) {
    case menu_state:
        if (IsKeyPressed(KEY_ENTER)) {
            current_level_index = 0;
            dollars = 0;
            lives = max_lives;
            upgrade_wide_paddle = false;
            upgrade_slow_ball = false;

            load_level();
            game_state = in_game_state;
        }
        break;

    case in_game_state:
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            move_paddle(-paddle_speed);
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            move_paddle(paddle_speed);
        }
        // For Debugging
//        if (IsKeyPressed(KEY_N))
//        {
//            load_level(1);
//        }

        move_ball();
        if (is_ball_touching_bottom()) {
            lives--;
            PlaySound(lose_sound);

            if (lives <= 0) {
                game_state = game_over_state;
                ClearBackground(BLACK);
                init_game_over_menu();
                break;
            }

            reset_ball();
            reset_paddle();
            break;
        }

        if (current_level_blocks == 0) {
            PlaySound(win_sound);
            init_shop_menu();
            game_state = shop_state;
            is_live_added = false;
        }
        break;
    case victory_state:
        if (IsKeyPressed(KEY_ENTER)) {
            load_level();
            game_state = in_game_state;
        }
        break;
    case game_over_state:
        current_level_index = 0;
        dollars = 0;
        upgrade_wide_paddle = false;
        upgrade_slow_ball = false;
        draw_game_over_menu();
        if (IsKeyPressed(KEY_ENTER)) {
            lives = max_lives;
            load_level();
            game_state = in_game_state;
        }
        break;
    case shop_state:
    {
        if (shop_music_loaded && !shopping_music_playing) {
            PlayMusicStream(shopping_music);
            shopping_music_playing = true;
        }
        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
            if (dollars >= price_extra_life && lives < max_lives) {
                dollars -= price_extra_life;
                lives += 1;
                is_live_added = true;
                PlaySound(choice_sound);
            }
        }

        if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
            if (!upgrade_wide_paddle && dollars >= price_wide_paddle) {
                dollars -= price_wide_paddle;
                upgrade_wide_paddle = true;
                PlaySound(choice_sound);
            }
        }

        if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) {
            if (!upgrade_slow_ball && dollars >= price_slow_ball) {
                dollars -= price_slow_ball;
                upgrade_slow_ball = true;
                PlaySound(choice_sound);
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (shop_music_loaded && shopping_music_playing) {
                StopMusicStream(shopping_music);
                shopping_music_playing = false;
            }
            load_level(1);
            game_state = in_game_state;
        }
        break;
    }
    }
}

void draw()
{
    switch (game_state) {
    case menu_state:
        draw_menu();
        break;
    case in_game_state:
        draw_level();
        draw_paddle();
        draw_ball();
        draw_ui();
        break;
    case paused_state:
        draw_level();
        draw_paddle();
        draw_ball();
        draw_ui();
        draw_pause_menu();
        break;

    case victory_state:
        draw_victory_menu();
        break;
    case game_over_state:
        draw_game_over_menu();
        break;
    case shop_state:
        draw_shop_menu();
        break;
    }
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Breakout");
    SetExitKey(0);
    SetTargetFPS(60);

    load_fonts();
    load_textures();
    load_level();
    load_sounds();

    while (!WindowShouldClose()) {
        BeginDrawing();

        draw();
        update();

        EndDrawing();
    }
    CloseWindow();

    unload_sounds();
    unload_level();
    unload_textures();
    unload_fonts();

    return 0;
}