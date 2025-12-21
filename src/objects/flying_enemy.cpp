#include "flying_enemy.hpp"

#include <algorithm>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left, 
	const int width, 
	const int height, 
	const float y_range, 
	const float x_range
) : Enemy(top_left, width, height),
	  y_range(y_range),
	  x_range(x_range)
{
	vspeed = -0.25f;
	hspeed = 0.15f;
}

void FlyingEnemy::move_horizontally() noexcept {
	top_left.x += hspeed;
	moved_x += hspeed;

	if (std::abs(moved_x) >= x_range) {
		hspeed = -hspeed;
	}
}

void FlyingEnemy::move_vertically() noexcept {
	top_left.y += vspeed;
	moved_y += vspeed;

	if (std::abs(moved_y) >= y_range) {
		vspeed = -vspeed;
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* ) noexcept {
	top_left.y -= vspeed;
	vspeed = -vspeed;
}