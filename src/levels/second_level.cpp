#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return false;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({20, 10}, 3, 3);
	
	ui_factory->create_ship({20, 20}, 40, 5);
	ui_factory->create_ship({60, 15}, 10, 10);
	ui_factory->create_ship({80, 20}, 20, 5);
	ui_factory->create_ship({120, 15}, 10, 10);
	ui_factory->create_ship({150, 20}, 40, 5);
	ui_factory->create_ship({210, 15}, 10, 10);
	
	ui_factory->create_enemy({45, 10}, 3, 2);
	ui_factory->create_enemy({80, 10}, 3, 2);
	ui_factory->create_enemy({65, 10}, 3, 2);
	ui_factory->create_enemy({120, 10}, 3, 2);
	ui_factory->create_enemy({160, 10}, 3, 2);
	ui_factory->create_enemy({175, 10}, 3, 2);
}
