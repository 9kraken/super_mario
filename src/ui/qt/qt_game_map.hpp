#pragma once

#include <QGraphicsScene>
#include <vector>

#include "game_map.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
    class QtGameMap : public GameMap {
    private:
        QGraphicsScene* scene_ = nullptr;
        std::vector<QtUIObject*> objs;

    public:
        QtGameMap(const int height, const int width);
        ~QtGameMap();

        QGraphicsScene* scene() { return scene_; }

        void add_obj(QtUIObject* obj);
        void clear() noexcept override;
        void refresh() noexcept override;
        void remove_obj(QtUIObject* obj);
        void remove_objs() override;
        void show() const noexcept override;  // Не нужно для Qt, но для совместимости
    };
}