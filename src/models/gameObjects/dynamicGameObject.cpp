#include "models/gameObjects/dynamicGameObject.h"



DynamicGameObject::DynamicGameObject(const DynamicGameObjectParams& params, QObject* parent)
    : GameObject(params, parent),
      _velocity(params.velocity),
      _rotation(params.rotation),
      _radius(params.radius)
{ }

void DynamicGameObject::updatePosition(qreal deltaTime)
{
    if (_velocity.isNull()) return;

    QPointF currentPos = position();
    QPointF nextPos = currentPos + (_velocity.toPointF() * deltaTime);

    setPosition(nextPos);
}

QVector2D DynamicGameObject::velocity() const noexcept
    { return _velocity; }

void DynamicGameObject::setVelocity(const QVector2D &newVelocity)
    { _velocity = newVelocity; }

qreal DynamicGameObject::rotation() const noexcept
    { return _rotation; }

void DynamicGameObject::setRotation(qreal newRotation)
{
    if (newRotation == _rotation) {
        return;
    }
    _rotation = newRotation;
    emit rotationChanged();
}

qreal DynamicGameObject::radius() const noexcept
    { return _radius; }
