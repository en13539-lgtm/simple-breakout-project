#include "assets.h"
#include "ball.h"
#include "game.h"
#include "graphics.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

void update()
{
    switch (game_state) {
    case menu_state:
        if (IsKeyPressed(KEY_ENTER)) {
            lives = max_lives;
            load_level();
            game_state = in_game_state;
        }
        break;

    case in_game_state:
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = paused_state;
            break;
        }

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
            load_level(1);
            PlaySound(win_sound);
            game_state = victory_state;
        }
        break;

    case paused_state:
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = in_game_state;
        }
        break;

    case victory_state:
        if (IsKeyPressed(KEY_ENTER)) {
            load_level();
            game_state = in_game_state;
        }
        break;
    case game_over_state:
        if (IsKeyPressed(KEY_ENTER)) {
            lives = max_lives;
            load_level();
            game_state = in_game_state;
        }
        break;

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
    }
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Breakout");
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