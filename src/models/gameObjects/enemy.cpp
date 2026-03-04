#include <QVector2D>

#include "models/gameObjects/enemy.h"



Enemy::Enemy(const EnemyParams& params, QObject* parent)
    : Unit(params, parent),
      _targetRadius(params.targetRadius)
{ }

qreal Enemy::targetRadius() const noexcept
    { return _targetRadius; }

void Enemy::setTargetRadius(const qreal newTargetRadius)
    { _targetRadius = newTargetRadius; }
