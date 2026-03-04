#pragma once

#include "models/gameObjects/dynamicGameObject.h"



struct UnitParams : DynamicGameObjectParams
{
    qreal speed = 0.0;
    qreal hp = 1.0;
};

class Unit : public DynamicGameObject
{
    Q_OBJECT
    Q_PROPERTY(qreal hp READ hp NOTIFY hpChanged)

public:
    explicit Unit(const UnitParams& params, QObject* parent = nullptr);

    void takeDamage(qreal damage);

    qreal speed() const noexcept;
    qreal hp() const noexcept;

signals:
    void hpChanged();

private:
    qreal _speed;
    qreal _hp;
};
