#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({20, 10}, 3, 3);
	
	ui_factory->create_ship({20, 20}, 40, 5);
	ui_factory->create_ship({80, 20}, 15, 5);
	ui_factory->create_ship({110, 15}, 15, 10);
	ui_factory->create_ship({140, 10}, 15, 15);
	
	ui_factory->create_enemy({25, 10}, 3, 2);
	ui_factory->create_enemy({50, 10}, 3, 2);
	ui_factory->create_enemy({80, 10}, 3, 2);
	ui_factory->create_enemy({90, 10}, 3, 2);
	ui_factory->create_enemy({120, 10}, 3, 2);
}
