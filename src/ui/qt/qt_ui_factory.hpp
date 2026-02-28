#pragma once

#include <vector>

#include "qt_box.hpp"
#include "qt_enemy.hpp"
#include "qt_flying_enemy.hpp"
#include "qt_full_box.hpp"
#include "qt_jumping_enemy.hpp"
#include "qt_game_map.hpp"
#include "qt_mario.hpp"
#include "qt_money.hpp"
#include "qt_ship.hpp"
#include "ui_factory.hpp"
#include "game_level.hpp"

namespace biv {
    class QtUIFactory : public UIFactory {
    private:
        QtGameMap* game_map_qt = nullptr;
        std::vector<QtBox*> boxes;
        std::vector<QtFullBox*> full_boxes;
        std::vector<QtShip*> ships;
        QtMario* mario = nullptr;
        std::vector<QtEnemy*> enemies;
        std::vector<QtFlyingEnemy*> flying_enemies;
        std::vector<QtJumpingEnemy*> jumping_enemies;
        std::vector<QtMoney*> moneys;
        GameLevel* current_level = nullptr;

    public:
        QtUIFactory(Game* game);

        void clear_data() override;
        void create_box(const Coord& top_left, const int width, const int height) override;
        void create_enemy(const Coord& top_left, const int width, const int height) override;
        void create_flying_enemy(const Coord& top_left, const int width, const int height) override;
        void create_full_box(const Coord& top_left, const int width, const int height) override;
        void create_jumping_enemy(const Coord& top_left, const int width, const int height) override;
        void create_mario(const Coord& top_left, const int width, const int height) override;
        void create_money(const Coord& top_left, const int width, const int height) override;
        void create_ship(const Coord& top_left, const int width, const int height) override;
        GameMap* get_game_map() override;
        Mario* get_mario() override;

        QtGameMap* get_game_map_qt();
        GameLevel* get_current_level();
        void set_current_level(GameLevel* level);
        void sync_model_to_view();  // Синхронизирует позиции Qt-итемов с моделью

    private:
        void create_game_map() override;
    };
}