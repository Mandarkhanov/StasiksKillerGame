#pragma once

#include "models/gameObjects/dynamicGameObject.h"



struct BulletParams : public DynamicGameObjectParams
{
    qreal damage = 10.0;
};

class Bullet : public DynamicGameObject {
    Q_OBJECT

public:
    explicit Bullet(const BulletParams& params, QObject* parent = nullptr);

    qreal damage() const noexcept;

private:
    qreal _damage;
};
