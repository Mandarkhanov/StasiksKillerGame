#pragma once

#include "models/gameObjects/unit.h"

struct PlayerParams : public UnitParams
{
    QVector2D localGunOffset = {0.0, 0.0};
    qreal exp = 0.0;
};

class Player : public Unit
{
    Q_OBJECT
    Q_PROPERTY(qreal exp READ exp NOTIFY expChanged)

public:
    explicit Player(const PlayerParams& params, QObject* parent = nullptr);

    QPointF gunPos() const;

    qreal exp() const noexcept;
    void addExp(qreal amount);

signals:
    void expChanged();

private:
    QVector2D _localGunOffset;
    qreal _exp;
};
