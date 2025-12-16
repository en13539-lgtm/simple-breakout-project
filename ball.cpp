#include "ball.h"
#include "assets.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

#include <cmath>
#include <numbers>

void spawn_ball()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == BALL) {
                set_level_cell(row, column, VOID);
                ball_spawn_pos = { static_cast<float>(column), static_cast<float>(row) };
                reset_ball();
                goto outer_loop_end;
            }
        }
    }
outer_loop_end:;
}

void move_ball()
{
    Vector2 next_ball_pos = {
        ball_pos.x + ball_vel.x,
        ball_pos.y + ball_vel.y
    };

    if (is_colliding_with_level_cell(next_ball_pos, ball_size, COIN)) {
        char& coin_cell = get_colliding_level_cell(next_ball_pos, ball_size, COIN);
        coin_cell = VOID;

        dollars += dollars_per_coin;
        PlaySound(cache_sound);
    }

    if (is_colliding_with_level_cell(next_ball_pos, ball_size, WALL)) {
        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, WALL)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, WALL)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }
    } else if (is_colliding_with_level_cell(next_ball_pos, ball_size, BLOCKS)) {
        char& temp = get_colliding_level_cell(next_ball_pos, ball_size, BLOCKS);

        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, BLOCKS)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, BLOCKS)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }

        temp = VOID;
        --current_level_blocks;
    } else if (is_colliding_with_paddle(next_ball_pos, ball_size)) {
        ball_vel.y = -std::abs(ball_vel.y);
    }

    ball_pos = next_ball_pos;
}

void reset_ball()
{
    ball_pos = ball_spawn_pos;
    constexpr float ball_launch_angle_radians =
        ball_launch_angle_degrees * (std::numbers::pi_v<float> / 180.0f);

    ball_vel.y = -ball_launch_vel_mag * std::sin(ball_launch_angle_radians);
    ball_vel.x = (rand() % 2 == 0)
        ?  ball_launch_vel_mag * std::cos(ball_launch_angle_radians)
        : -ball_launch_vel_mag * std::cos(ball_launch_angle_radians);
}

bool is_ball_touching_bottom()
{
    return (ball_pos.y + ball_size.y) >= (static_cast<float>(current_level.rows) - 1.0f);
}

bool is_ball_inside_level()
{
    return is_inside_level(static_cast<int>(ball_pos.y), static_cast<int>(ball_pos.x));
}
