#include "qt_enemy.hpp"
#include <QPainter>

using biv::QtEnemy;

QtEnemy::QtEnemy(const Coord& top_left, const int width, const int height) 
    : Enemy(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtEnemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::red);  // Красный цвет для врага 'e'
    painter->drawRect(boundingRect());
}
