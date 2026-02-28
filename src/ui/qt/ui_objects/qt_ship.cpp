#include "qt_ship.hpp"
#include <QPainter>

using biv::QtShip;

QtShip::QtShip(const Coord& top_left, const int width, const int height) 
    : Ship(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtShip::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::darkGray);
    painter->drawRect(boundingRect());
}
