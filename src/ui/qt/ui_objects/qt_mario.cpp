#include "qt_mario.hpp"
#include <QPainter>

using biv::QtMario;

QtMario::QtMario(const Coord& top_left, const int width, const int height) 
    : Mario(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtMario::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}
