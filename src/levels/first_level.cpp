#include "first_level.hpp"

#include "second_level.hpp"

using biv::FirstLevel;

FirstLevel::FirstLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* FirstLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::SecondLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void FirstLevel::init_data() {
	ui_factory->create_mario({20, 10}, 3, 3);
	
	ui_factory->create_ship({20, 20}, 40, 5);
	
	ui_factory->create_full_box({30, 10}, 5, 3);
	ui_factory->create_full_box({50, 10}, 5, 3);
	
	ui_factory->create_ship({60, 15}, 40, 10);
	
	ui_factory->create_box({60, 5}, 10, 3);
	ui_factory->create_full_box({70, 5}, 5, 3);
	ui_factory->create_box({75, 5}, 5, 3);
	ui_factory->create_full_box({80, 5}, 5, 3);
	ui_factory->create_box({85, 5}, 10, 3);
	
	ui_factory->create_ship({100, 20}, 20, 5);
	ui_factory->create_ship({120, 15}, 10, 10);
	ui_factory->create_ship({150, 15}, 10, 10);
	ui_factory->create_ship({180, 15}, 10, 10);
	
	ui_factory->create_enemy({45, 10}, 3, 2);
	ui_factory->create_enemy({80, 10}, 3, 2);
}
