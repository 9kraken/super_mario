#include "qt_money.hpp"
#include <QPainter>

using biv::QtMoney;

QtMoney::QtMoney(const Coord& top_left, const int width, const int height) 
    : Money(top_left, width, height), QtUIObjectRectAdapter(top_left, width, height) {}

void QtMoney::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::green);  // Зеленый цвет для денег '$'
    painter->drawRect(boundingRect());
}
