#include "qt_game_map.hpp"
#include <QGraphicsRectItem>

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width) : GameMap(height, width) {
    scene_ = new QGraphicsScene(0, 0, width * 10, height * 10);
    // Фон: воздух - белый, вода - синий
    scene_->setBackgroundBrush(Qt::white);
    QGraphicsRectItem* water = new QGraphicsRectItem(0, (height - 3) * 10, width * 10, 3 * 10);
    water->setBrush(QColor(0, 0, 255));  // Синий
    scene_->addItem(water);
}

QtGameMap::~QtGameMap() {
    delete scene_;
}

void QtGameMap::add_obj(QtUIObject* obj) {
    objs.push_back(obj);
    scene_->addItem(obj);
}

void QtGameMap::clear() noexcept {
    for (auto item : scene_->items()) {
        scene_->removeItem(item);
    }
}

void QtGameMap::refresh() noexcept {
    // В Qt refresh не нужен, так как tick обновляет сцену
}

void QtGameMap::remove_obj(QtUIObject* obj) {
    if (obj == nullptr) return;
    auto it = std::remove(objs.begin(), objs.end(), obj);
    objs.erase(it, objs.end());
    scene_->removeItem(obj);
}

void QtGameMap::remove_objs() {
    objs.clear();
    clear();
}

void QtGameMap::show() const noexcept {
    // Не нужно для Qt
}