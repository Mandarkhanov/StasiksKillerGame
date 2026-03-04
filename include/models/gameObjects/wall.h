#pragma once

#include <QRectF>
#include <QSizeF>
#include "models/gameObjects/gameObject.h"

struct WallParams : GameObjectParams
{
    QSizeF size;
};

class Wall : public GameObject
{
    Q_OBJECT
    Q_PROPERTY(QSizeF size READ size CONSTANT)

public:
    explicit Wall(const WallParams& params, QObject* parent = nullptr);

    QRectF rect() const noexcept;
    QSizeF size() const noexcept;
    qreal width() const noexcept;
    qreal height() const noexcept;

private:
    QSizeF _size;
};
