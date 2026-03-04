#include "models/gameObjects/unit.h"



Unit::Unit(const UnitParams& params, QObject* parent)
    : DynamicGameObject(params, parent),
      _speed(params.speed),
      _hp(params.hp)
{ }

void Unit::takeDamage(qreal damage)
{
    if (damage <= 0) {
        return;
    }

    _hp -= damage;
    if (_hp < 0) {
        _hp = 0;
    }

    emit hpChanged();
}

qreal Unit::speed() const noexcept
    { return _speed; }

qreal Unit::hp() const noexcept
    { return _hp; }
