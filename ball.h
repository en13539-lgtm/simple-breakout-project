#ifndef BALL_H
#define BALL_H

#include "raylib.h"

inline constexpr float ball_launch_vel_mag = 0.15f;
inline constexpr float ball_launch_angle_degrees = 49.6f;
inline constexpr Vector2 ball_size = { 1.0f, 1.0f };

inline Vector2 ball_pos;
inline Vector2 ball_vel;

void spawn_ball();
void move_ball();
bool is_ball_inside_level();

inline Vector2 ball_spawn_pos;

void reset_ball();
bool is_ball_touching_bottom();

#endif // BALL_H
