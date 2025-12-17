#include "graphics.h"

#include "assets.h"
#include "ball.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

#include <cmath>
#include <iostream>
#include <string>

struct Text {
    std::string str;
    Vector2 position = { 0.50f, 0.50f };
    float size = 32.0f;
    Color color = WHITE;
    float spacing = 4.0f;
    Font* font = nullptr;
};

constexpr float cell_scale = 0.6f;
constexpr float screen_scale_divisor = 700.0f;

constexpr size_t victory_ball_launch_degree_offset = 3;
constexpr size_t victory_balls_count = 360 / victory_ball_launch_degree_offset;
constexpr float victory_balls_speed = 7.0f;
constexpr float victory_balls_size = 3.0f;

Vector2 screen_size;
float screen_scale;
float cell_size;
Vector2 shift_to_center;

Vector2 victory_balls_pos[victory_balls_count];
Vector2 victory_balls_vel[victory_balls_count];

size_t game_frame = 0;

void draw_image(const Texture2D& image, const float x, const float y, const float width, const float height)
{
    const Rectangle source = { 0.0f, 0.0f, static_cast<float>(image.width), static_cast<float>(image.height) };
    const Rectangle destination = { x, y, width, height };
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void draw_image(const Texture2D& image, const float x, const float y, const float size)
{
    draw_image(image, x, y, size, size);
}

void draw_sprite(sprite& sprite, const float x, const float y, const float width, const float height)
{
    draw_image(sprite.frames[sprite.frame_index], x, y, width, height);

    if (sprite.prev_game_frame == game_frame) {
        return;
    }
    if (sprite.frames_skipped < sprite.frames_to_skip) {
        ++sprite.frames_skipped;
    } else {
        sprite.frames_skipped = 0;

        ++sprite.frame_index;
        if (sprite.frame_index >= sprite.frame_count) {
            sprite.frame_index = sprite.loop ? 0 : sprite.frame_count - 1;
        }
    }
    sprite.prev_game_frame = game_frame;
}

void draw_sprite(sprite& sprite, const float x, const float y, const float size)
{
    draw_sprite(sprite, x, y, size, size);
}

void draw_text(const Text& text)
{
    const auto [x, y] = MeasureTextEx(*text.font, text.str.c_str(), text.size * screen_scale, text.spacing);
    const Vector2 pos = {
        screen_size.x * text.position.x - 0.5f * x,
        screen_size.y * text.position.y - 0.5f * y
    };
    DrawTextEx(*text.font, text.str.c_str(), pos, y, text.spacing, text.color);
}

void derive_graphics_metrics()
{
    screen_size.x = static_cast<float>(GetScreenWidth());
    screen_size.y = static_cast<float>(GetScreenHeight());

    cell_size = std::min(screen_size.x / static_cast<float>(current_level.columns), screen_size.y / static_cast<float>(current_level.rows));
    screen_scale = std::min(screen_size.x, screen_size.y) / screen_scale_divisor;

    const float level_width = static_cast<float>(current_level.columns) * cell_size;
    const float level_height = static_cast<float>(current_level.rows) * cell_size;
    shift_to_center = {
        (screen_size.x - level_width) * 0.5f,
        (screen_size.y - level_height)
    };
}

void draw_heart(Vector2 center, float scale, Color color, float thickness = 2.5f)
{
    const int POINTS = 200;
    Vector2 prev{};

    for (int i = 0; i <= POINTS; i++)
    {
        float t = (float)i / (float)POINTS * 2.0f * PI;

        float x = 16.0f * powf(sinf(t), 3.0f);
        float y = -(13.0f * cosf(t)
            - 5.0f * cosf(2.0f * t)
            - 2.0f * cosf(3.0f * t)
            - 1.0f * cosf(4.0f * t));

        Vector2 p = {
            center.x + x * scale,
            center.y + y * scale
        };

        if (i > 0) DrawLineEx(prev, p, thickness, color);
        prev = p;
    }
}


void draw_menu()
{
    ClearBackground(BLACK);

    const Text game_title = {
        "Breakout",
        { 0.50f, 0.50f },
        200.0f,
        RED,
        4.0f,
        &menu_font
    };
    draw_text(game_title);

    const Text game_subtitle = {
        "Press Enter to Start",
        { 0.50f, 0.65f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(game_subtitle);
}

void draw_ui()
{
    const Text dollars_counter = {
        "$" + std::to_string(dollars),
        { 0.10f, 0.0375f },
        48.0f,
        GOLD,
        4.0f,
        &menu_font
    };
    draw_text(dollars_counter);

    const Text level_counter = {
        "LEVEL " + std::to_string(current_level_index + 1) + " OUT OF " + std::to_string(level_count),
        { 0.5f, 0.0375f },
        48.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(level_counter);

    const float baseX = screen_size.x * 0.08f;
    const float baseY = screen_size.y * 0.93f;
    const float spacing = 48.0f;
    const float scale = 1.6f;
    const float thickness = 5.5f;

    for (int i = 0; i < max_lives; ++i) {
        Color c = (i < lives) ? RED : DARKGRAY;
        Vector2 center = { baseX + i * spacing, baseY };
        draw_heart(center, scale, c, thickness);
    }


    const Text boxes_remaining = {
        "BLOCKS " + std::to_string(current_level_blocks),
        { 0.5f, 0.9625f },
        48.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(boxes_remaining);
}

void init_shop_menu()
{
}

void draw_shop_menu()
{
    ClearBackground(BLACK);

    const Text title = { "SHOP", {0.5f, 0.18f}, 110.0f, YELLOW, 4.0f, &menu_font };
    draw_text(title);
    const Text money = { "MONEY: $" + std::to_string(dollars), {0.5f, 0.30f}, 42.0f, GREEN, 4.0f, &menu_font };
    draw_text(money);
    const Text i1 = { "[1] +1 LIFE   - $" + std::to_string(price_extra_life),
        {0.5f, 0.42f}, 36.0f, WHITE, 4.0f, &menu_font };
    draw_text(i1);
    const Text i2 = { std::string("[2] WIDE PADDLE - $") + std::to_string(price_wide_paddle)
            + (upgrade_wide_paddle ? " (OWNED)" : ""),
        {0.5f, 0.50f}, 36.0f, WHITE, 4.0f, &menu_font };
    draw_text(i2);
    const Text i3 = { std::string("[3] SLOW BALL - $") + std::to_string(price_slow_ball)
            + (upgrade_slow_ball ? " (OWNED)" : ""),
        {0.5f, 0.58f}, 36.0f, WHITE, 4.0f, &menu_font };
    draw_text(i3);
    const Text hint = { "Press ENTER to continue", {0.5f, 0.75f}, 32.0f, GRAY, 4.0f, &menu_font };
    draw_text(hint);
}

void draw_level()
{
    ClearBackground(BLACK);

    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            const char data = current_level.data[row * current_level.columns + column];
            const float texture_x_pos = shift_to_center.x + static_cast<float>(column) * cell_size;
            const float texture_y_pos = shift_to_center.y + static_cast<float>(row) * cell_size;

            switch (data) {
            case WALL:
                draw_image(wall_texture, texture_x_pos, texture_y_pos, cell_size);
                break;
            case BLOCKS:
                draw_image(block_texture, texture_x_pos, texture_y_pos, cell_size);
                break;
            case COIN: {
                const Vector2 center = { texture_x_pos + cell_size * 0.5f, texture_y_pos + cell_size * 0.5f };
                DrawCircleV(center, cell_size * 0.30f, GOLD);
                DrawCircleV({ center.x - cell_size * 0.08f, center.y - cell_size * 0.08f }, cell_size * 0.08f, { 255, 255, 255, 140 });
                break;
            }
            default:;
            }
        }
    }
}

void draw_paddle()
{
    const float texture_x_pos = shift_to_center.x + paddle_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + paddle_pos.y * cell_size;
    draw_image(paddle_texture, texture_x_pos, texture_y_pos, paddle_size.x * cell_size, paddle_size.y * cell_size);
}

void draw_ball()
{
    const float texture_x_pos = shift_to_center.x + ball_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + ball_pos.y * cell_size;
    draw_sprite(ball_sprite, texture_x_pos, texture_y_pos, cell_size);
}

void draw_pause_menu()
{
    ClearBackground(BLACK);

    const Text paused_title = {
        "Press Escape to Resume",
        { 0.50f, 0.50f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(paused_title);
}

void init_victory_menu()
{
    for (size_t i = 0; i < victory_balls_count; ++i) {
        victory_balls_pos[i] = { screen_size.x / 2, screen_size.y / 2 };
        victory_balls_vel[i] = {
            std::cos(static_cast<float>(i * victory_ball_launch_degree_offset)) * victory_balls_speed,
            std::sin(static_cast<float>(i * victory_ball_launch_degree_offset)) * victory_balls_speed
        };
    }
}

void animate_victory_menu()
{
    for (size_t i = 0; i < victory_balls_count; ++i) {
        if (victory_balls_pos[i].x + victory_balls_vel[i].x > screen_size.x || victory_balls_pos[i].x + victory_balls_vel[i].x < 0) {
            victory_balls_vel[i].x *= -1.0f;
        }
        if (victory_balls_pos[i].y + victory_balls_vel[i].y > screen_size.y || victory_balls_pos[i].y + victory_balls_vel[i].y < 0) {
            victory_balls_vel[i].y *= -1.0f;
        }
        victory_balls_pos[i] = {
            victory_balls_pos[i].x + victory_balls_vel[i].x,
            victory_balls_pos[i].y + victory_balls_vel[i].y
        };
    }
}

void draw_victory_menu()
{
    animate_victory_menu();

    DrawRectangleV({ 0.0f, 0.0f }, { screen_size.x, screen_size.y }, { 0, 0, 0, 50 });

    for (const auto& [x, y] : victory_balls_pos) {
        DrawCircleV({ x, y }, victory_balls_size, WHITE);
    }

    const Text victory_title = {
        "Victory!",
        { 0.50f, 0.50f },
        100.0f,
        RED,
        4.0f,
        &menu_font
    };
    draw_text(victory_title);

    const Text victory_subtitle = {
        "Press Enter to Restart",
        { 0.50f, 0.65f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(victory_subtitle);
}


void init_game_over_menu()
{
    init_victory_menu();
}

void draw_game_over_menu()
{
    animate_victory_menu();
    DrawRectangleV({ 0.0f, 0.0f }, { screen_size.x, screen_size.y }, { 0, 0, 0, 50 });

    for (const auto& [x, y] : victory_balls_pos) {
        DrawCircleV({ x, y }, victory_balls_size, WHITE);
    }

    const Text title = {
        "Game Over",
        { 0.50f, 0.50f },
        100.0f,
        RED,
        4.0f,
        &menu_font
    };
    draw_text(title);

    const Text subtitle = {
        "Press Enter to Start New Game",
        { 0.50f, 0.65f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(subtitle);
}
