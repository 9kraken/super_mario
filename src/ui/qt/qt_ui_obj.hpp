#pragma once

#include <QGraphicsItem>

namespace biv {
    class QtUIObject : public QGraphicsItem {
    public:
        virtual void sync_position() = 0;  // Синхронизирует позицию с моделью
    };
}