#include "qt_ui_obj_rect_adapter.hpp"
#include <QPainter>

using biv::QtUIObjectRectAdapter;

QtUIObjectRectAdapter::QtUIObjectRectAdapter(const Coord& top_left, const int width, const int height) {
    this->top_left = top_left;
    this->width = width;
    this->height = height;
    setPos(top_left.x * 15, top_left.y * 15);
}

QRectF QtUIObjectRectAdapter::boundingRect() const {
    return QRectF(0, 0, width * 15, height * 15);
}

void QtUIObjectRectAdapter::sync_position() {
    setPos(get_x() * 15, get_y() * 15);
}