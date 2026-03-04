#pragma once

#include <QObject>
#include <QPointF>
#include <QString>

#include "models/gameObjects/gameTypes.h"



struct GameObjectParams
{
    GameTypes::ObjectType type = GameTypes::ObjectType::Unknown;
    QPointF position = {0.0, 0.0};
    QString texturePath = "";
    qreal visualScale = 1.0;
};

class GameObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString texturePath READ texturePath CONSTANT)
    Q_PROPERTY(qreal visualScale READ visualScale CONSTANT)

public:
    explicit GameObject(const GameObjectParams& params, QObject* parent = nullptr);
    virtual ~GameObject() {};

    GameTypes::ObjectType type() const noexcept;

    QPointF position() const noexcept;
    void setPosition(const QPointF& newPosition);

    QString texturePath() const noexcept;

    qreal visualScale() const noexcept;

signals:
    void positionChanged();

private:
    GameTypes::ObjectType _type;
    QPointF _position;
    QString _texturePath;
    qreal _visualScale;
};
