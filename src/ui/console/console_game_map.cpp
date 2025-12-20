#include "console_game_map.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <os_control_settings.hpp>

using biv::ConsoleGameMap;

ConsoleGameMap::ConsoleGameMap(const int height, const int width) 
	: GameMap(height, width) {

	map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width + 1];
		memset(map[i], ' ', width);
		map[i][width] = '\0';
	}
		 
	clear();
}

ConsoleGameMap::~ConsoleGameMap() {
	for (int i = 0; i < height; i++) {
		delete [] map[i];
	}
	delete [] map;
}

void ConsoleGameMap::add_obj(ConsoleUIObject* obj) {
	objs.push_back(obj);
}

void ConsoleGameMap::clear() noexcept {
    for (int i = 0; i < width; i++) {
        map[0][i] = ' ';
    }
    map[0][width] = '\0';
    for (int j = 1; j < height; j++) {
        std::copy(map[0], map[0] + width + 1, map[j]);
    }
}

void ConsoleGameMap::refresh() noexcept {
	clear();

	// Воздух
	std::fill(map[0], map[0] + width, ' ');
	map[0][width] = '\0';

	for (int i = 1; i < height - 3; i++) {
		std::copy(map[0], map[0] + width + 1, map[i]);
	}

	// Вода
	std::fill(map[height - 3], map[height - 3] + width, '~');
	map[height - 3][width] = '\0';

	for (int i = height - 2; i < height; i++) {
		std::copy(map[height - 3], map[height - 3] + width + 1, map[i]);
	}
	
	// Объекты карты
	for (ConsoleUIObject* obj: objs) {
		int left = obj->get_left();
		int top = obj->get_top();
		int right = obj->get_right();
		int bottom = obj->get_bottom();
		
		char brush = obj->get_brush();
		
		for (int i = left; i < right; i++) {
			for (int j = top; j < bottom; j++) {
				if (is_on_map(i, j)) {
					map[j][i] = brush;
				}
			}
		}
	}
}

void ConsoleGameMap::remove_obj(ConsoleUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void ConsoleGameMap::remove_objs() {
	objs.clear();
}

void ConsoleGameMap::show() const noexcept {
	biv::os::set_cursor_start_position();

	char* buffer = new char[height * (width + 2)];
	int pos = 0;
	
	for (int i = 0; i < height; i++) {
		//std::memcpy(buffer + pos, map[i], width);
		strcpy_s(buffer + pos, width + 1, map[i]);
		pos += width;
		buffer[pos++] = '\n';
	}
	buffer[pos] = '\0';
	
	// Вывод всего буфера одним вызовом
	std::cout << buffer << std::flush;
	delete[] buffer;
}
