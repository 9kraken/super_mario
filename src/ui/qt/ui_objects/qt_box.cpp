#include "qt_box.hpp"
#include <QPainter>

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height) 
    : Box(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::gray);  // Аналог '-'
    painter->drawRect(boundingRect());
}
