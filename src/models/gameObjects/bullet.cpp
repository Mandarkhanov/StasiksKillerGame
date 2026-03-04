#include "models/gameObjects/bullet.h"



Bullet::Bullet(const BulletParams& params, QObject* parent)
    : DynamicGameObject(params, parent),
      _damage(params.damage)
{ }

qreal Bullet::damage() const noexcept
    { return _damage; }
