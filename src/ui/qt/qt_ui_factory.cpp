#include "qt_ui_factory.hpp"

using biv::QtUIFactory;

QtUIFactory::QtUIFactory(Game* game) : UIFactory(game) {
    create_game_map();
}

void QtUIFactory::clear_data() {
    game->remove_objs();
    game_map_qt->remove_objs();
    delete mario;
    mario = nullptr;
    boxes.clear();
    full_boxes.clear();
    ships.clear();
    enemies.clear();
    flying_enemies.clear();
    jumping_enemies.clear();
    moneys.clear();
}

void QtUIFactory::create_box(const Coord& top_left, const int width, const int height) {
    QtBox* box = new QtBox(top_left, width, height);
    boxes.push_back(box);
    game->add_map_movable(box);
    game->add_static_obj(box);
    game_map_qt->add_obj(box);
}

void QtUIFactory::create_enemy(const Coord& top_left, const int width, const int height) {
    QtEnemy* enemy = new QtEnemy(top_left, width, height);
    enemies.push_back(enemy);
    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
    game_map_qt->add_obj(enemy);
}

void QtUIFactory::create_flying_enemy(const Coord& top_left, const int width, const int height) {
    QtFlyingEnemy* flying_enemy = new QtFlyingEnemy(top_left, width, height);
    flying_enemies.push_back(flying_enemy);
    game->add_map_movable(flying_enemy);
    game->add_movable(flying_enemy);
    game->add_collisionable(flying_enemy);
    game_map_qt->add_obj(flying_enemy);
}

void QtUIFactory::create_full_box(const Coord& top_left, const int width, const int height) {
    QtFullBox* full_box = new QtFullBox(top_left, width, height, this);
    full_boxes.push_back(full_box);
    game->add_collisionable(full_box);
    game->add_map_movable(full_box);
    game->add_static_obj(full_box);
    game_map_qt->add_obj(full_box);
}

void QtUIFactory::create_jumping_enemy(const Coord& top_left, const int width, const int height) {
    QtJumpingEnemy* jumping_enemy = new QtJumpingEnemy(top_left, width, height);
    jumping_enemies.push_back(jumping_enemy);
    game->add_map_movable(jumping_enemy);
    game->add_movable(jumping_enemy);
    game->add_collisionable(jumping_enemy);
    game_map_qt->add_obj(jumping_enemy);
}

void QtUIFactory::create_mario(const Coord& top_left, const int width, const int height) {
    game->remove_collisionable(mario);
    game->remove_movable(mario);
    game->remove_mario();
    game_map_qt->remove_obj(mario);
    delete mario;
    mario = nullptr;

    mario = new QtMario(top_left, width, height);
    game->add_collisionable(mario);
    game->add_movable(mario);
    game->add_mario(mario);
    game_map_qt->add_obj(mario);
}

void QtUIFactory::create_money(const Coord& top_left, const int width, const int height) {
    QtMoney* money = new QtMoney(top_left, width, height);
    moneys.push_back(money);
    game->add_map_movable(money);
    game->add_movable(money);
    game->add_collisionable(money);
    game_map_qt->add_obj(money);
}

void QtUIFactory::create_ship(const Coord& top_left, const int width, const int height) {
    QtShip* ship = new QtShip(top_left, width, height);
    ships.push_back(ship);
    game->add_map_movable(ship);
    game->add_static_obj(ship);
    game_map_qt->add_obj(ship);
}

biv::GameMap* QtUIFactory::get_game_map() {
    return game_map_qt;
}

biv::Mario* QtUIFactory::get_mario() {
    return mario;
}

biv::QtGameMap* QtUIFactory::get_game_map_qt() {
    return game_map_qt;
}

biv::GameLevel* QtUIFactory::get_current_level() {
    return current_level;
}

void QtUIFactory::set_current_level(biv::GameLevel* level) {
    current_level = level;
}

void QtUIFactory::sync_model_to_view() {
    // Обновляем позиции всех Qt-объектов на основе модели
    for (auto obj : boxes) obj->sync_position();
    for (auto obj : full_boxes) obj->sync_position();
    for (auto obj : ships) obj->sync_position();
    if (mario) mario->sync_position();
    for (auto obj : enemies) obj->sync_position();
    for (auto obj : flying_enemies) obj->sync_position();
    for (auto obj : jumping_enemies) obj->sync_position();
    for (auto obj : moneys) obj->sync_position();
}

void QtUIFactory::create_game_map() {
    game_map_qt = new QtGameMap(30, 200);  // Те же размеры, что в консоли
}