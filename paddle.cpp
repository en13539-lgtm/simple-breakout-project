#include "paddle.h"
#include "level.h"

#include "raylib.h"

#include <cmath>

void spawn_paddle()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == PADDLE) {
                set_level_cell(row, column, VOID);
                paddle_spawn_pos = { static_cast<float>(column), static_cast<float>(row) };
                reset_paddle();
                goto outer_loop_end;
            }
        }
    }
outer_loop_end:;
}

void move_paddle(const float x_offset)
{
    float next_paddle_pos_x = paddle_pos.x + x_offset;
    if (!is_colliding_with_level_cell({ next_paddle_pos_x, paddle_pos.y }, paddle_size, WALL)) {
        paddle_pos.x = next_paddle_pos_x;
    }

    const float min_x = 1.0f;
    const float max_x = static_cast<float>(current_level.columns - 1) - paddle_size.x;
    if (paddle_pos.x < min_x) paddle_pos.x = min_x;
    if (paddle_pos.x > max_x) paddle_pos.x = max_x;
}

bool is_colliding_with_paddle(const Vector2 pos, const Vector2 size)
{
    const Rectangle paddle_hitbox = { paddle_pos.x, paddle_pos.y, paddle_size.x, paddle_size.y };
    const Rectangle hitbox = { pos.x, pos.y, size.x, size.y };
    return CheckCollisionRecs(paddle_hitbox, hitbox);
}

void reset_paddle()
{
    paddle_pos = paddle_spawn_pos;
    apply_paddle_upgrades();
}

void apply_paddle_upgrades()
{
    paddle_size = paddle_base_size;
    if (upgrade_wide_paddle) {
        paddle_size.x *= 1.45f;
    }
    const float min_x = 1.0f;
    const float max_x = static_cast<float>(current_level.columns - 1) - paddle_size.x;

    if (paddle_pos.x < min_x) paddle_pos.x = min_x;
    if (paddle_pos.x > max_x) paddle_pos.x = max_x;
}
