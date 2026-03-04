#pragma once

#include "models/gameObjects/unit.h"



struct EnemyParams : UnitParams
{
    qreal targetRadius;
};

class Enemy : public Unit
{
    Q_OBJECT

public:
    explicit Enemy(const EnemyParams& params, QObject* parent = nullptr);

    qreal targetRadius() const noexcept;
    void setTargetRadius(const qreal targetRadius);

private:
    qreal _targetRadius;
};
