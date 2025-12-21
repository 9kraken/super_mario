#pragma once

#include "enemy.hpp"

namespace biv {
	class FlyingEnemy : public Enemy {
		private:
			float moved_y = 0.0f;
			float y_range;

			float moved_x = 0.0f;
			float x_range;

		public:
			FlyingEnemy(
				const Coord& top_left, const int width, const int height,
				const float y_range = 3.0f, const float x_range = 10.0f
			);

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}