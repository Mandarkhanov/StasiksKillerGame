#pragma once

#include <QVector2D>

#include "models/gameObjects/gameObject.h"



struct DynamicGameObjectParams : public GameObjectParams
{
    QVector2D velocity = {0.0, 0.0};
    qreal rotation = 0.0;
    qreal radius = 10.0;
};

class DynamicGameObject : public GameObject
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius CONSTANT)
    Q_PROPERTY(qreal rotation READ rotation NOTIFY rotationChanged)

public:
    explicit DynamicGameObject(const DynamicGameObjectParams& params, QObject* parent = nullptr);
    virtual ~DynamicGameObject() {};

    virtual void updatePosition(qreal deltaTime);

    QVector2D velocity() const noexcept;
    void setVelocity(const QVector2D& newVelocity);

    qreal rotation() const noexcept;
    void setRotation(qreal newRotation);

    qreal radius() const noexcept;

signals:
    void rotationChanged();

private:
    QVector2D _velocity;
    qreal _rotation;
    qreal _radius;
};
