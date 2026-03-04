#include "models/gameObjects/gameObject.h"



GameObject::GameObject(const GameObjectParams& params, QObject* parent)
    : QObject(parent),
      _type(params.type),
      _position(params.position),
      _texturePath(params.texturePath),
      _visualScale(params.visualScale)
{ }

GameTypes::ObjectType GameObject::type() const noexcept
    { return _type; }

QPointF GameObject::position() const noexcept
    { return _position; }

void GameObject::setPosition(const QPointF& newPosition)
{
    if (_position == newPosition) {
        return;
    }
    _position = newPosition;
    emit positionChanged();
}

QString GameObject::texturePath() const noexcept
    { return _texturePath; }

qreal GameObject::visualScale() const noexcept
    { return _visualScale; }
