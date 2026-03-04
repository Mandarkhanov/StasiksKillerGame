#pragma once

#include <QObject>
#include <QSize>
#include <QList>
#include <QString>

#include "models/gameObjects/wall.h"



class GameMap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSize size READ size CONSTANT)
    Q_PROPERTY(QList<Wall*> walls READ walls CONSTANT)
    Q_PROPERTY(QString backgroundTexture READ backgroundTexture CONSTANT)

public:
    explicit GameMap(const QSize& size, QObject* parent = nullptr);

    QSize size() const noexcept;
    void setSize(const QSize& size);

    QList<Wall*> walls() const noexcept;

    void addWall(const QRectF& rect);
    void addWall(Wall* wall);

    QString backgroundTexture() const noexcept;
    void setBackgroundTexture(const QString& texturePath);

private:
    QSize _size;
    QList<Wall*> _walls;
    QString _backgroundTexture;
};
