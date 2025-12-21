#include "jumping_enemy.hpp"

#include <algorithm>

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
	const Coord& top_left, 
	const int width, 
	const int height
) : Enemy(top_left, width, height) {
	vspeed = 0.0f;
	hspeed = -0.15f;
}

void JumpingEnemy::move_vertically() noexcept {
    if (is_on_ground) {
        jump();
        is_on_ground = false;
    }
    Movable::move_vertically();
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	Enemy::process_vertical_static_collision(obj);
    is_on_ground = true;
}