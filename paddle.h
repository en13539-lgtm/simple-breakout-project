#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

inline constexpr Vector2 paddle_base_size = { 3.0f, 1.0f };
inline Vector2 paddle_size = paddle_base_size;

inline constexpr float paddle_speed = 0.1f;

inline Vector2 paddle_pos;
inline Vector2 paddle_spawn_pos;

void spawn_paddle();
void move_paddle(float x_offset);
bool is_colliding_with_paddle(Vector2 pos, Vector2 size);

void reset_paddle();
void apply_paddle_upgrades();

#endif // PADDLE_H
