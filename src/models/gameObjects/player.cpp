#include "models/gameObjects/player.h"



Player::Player(const PlayerParams& params, QObject* parent)
    : Unit(params, parent),
      _localGunOffset(params.localGunOffset),
      _exp(params.exp)
{ }

QPointF Player::gunPos() const
{
    qreal rad = qDegreesToRadians(rotation());

    qreal cosA = qCos(rad);
    qreal sinA = qSin(rad);

    qreal worldOffsetX = _localGunOffset.x() * cosA - _localGunOffset.y() * sinA;
    qreal worldOffsetY = _localGunOffset.x() * sinA + _localGunOffset.y() * cosA;

    return QPointF(position().x() + worldOffsetX, position().y() + worldOffsetY);
}

qreal Player::exp() const noexcept
    { return _exp; }

void Player::addExp(qreal amount)
{
    if (amount <= 0) {
        return;
    }
    _exp += amount;
    emit expChanged();
}
