#include "qt_full_box.hpp"
#include <QPainter>

using biv::QtFullBox;

QtFullBox::QtFullBox(const Coord& top_left, const int width, const int height, UIFactory* ui_factory) 
    : FullBox(top_left, width, height, ui_factory), QtUIObjectRectAdapter(top_left, width, height) {}

void QtFullBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (is_active_) {
        painter->setBrush(Qt::yellow);  // Желтый цвет для активного '?' 
    } else {
        painter->setBrush(Qt::gray);  // Серый цвет для неактивного '-'
    }
    painter->drawRect(boundingRect());
}
