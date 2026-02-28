#include "qt_jumping_enemy.hpp"
#include <QPainter>

using biv::QtJumpingEnemy;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height) 
    : JumpingEnemy(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtJumpingEnemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::darkRed);
    painter->drawRect(boundingRect());
}
