#include "models/gameObjects/wall.h"



Wall::Wall(const WallParams& params, QObject* parent)
    : GameObject(params, parent),
      _size(params.size)
{ }

QRectF Wall::rect() const noexcept
    { return QRectF(position().x(), position().y(), _size.width(), _size.height()); }

QSizeF Wall::size() const noexcept
    { return _size; }

qreal Wall::width() const noexcept
    { return _size.width(); }

qreal Wall::height() const noexcept
    { return _size.height(); }
