#include "qt_flying_enemy.hpp"
#include <QPainter>

using biv::QtFlyingEnemy;

QtFlyingEnemy::QtFlyingEnemy(const Coord& top_left, const int width, const int height) 
    : FlyingEnemy(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtFlyingEnemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::magenta);
    painter->drawRect(boundingRect());
}
