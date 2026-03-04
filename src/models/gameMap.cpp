#include "models/gameMap.h"



GameMap::GameMap(const QSize& size, QObject* parent)
    : QObject(parent),
      _size(size)
{ }

QSize GameMap::size() const noexcept
    { return _size; }

void GameMap::setSize(const QSize& size)
    { _size = size; }

QList<Wall*> GameMap::walls() const noexcept
    { return _walls; }

void GameMap::addWall(const QRectF& rect)
{
    WallParams params;
    params.type = GameTypes::ObjectType::Wall;
    params.position = rect.topLeft();
    params.size = rect.size();
    params.texturePath = "";
    addWall(new Wall(params, this));
}

void GameMap::addWall(Wall* wall)
{
    if (wall) {
        _walls.append(wall);

        if (wall->parent() == nullptr) {
            wall->setParent(this);
        }
    }
}

QString GameMap::backgroundTexture() const noexcept
    {return _backgroundTexture; }

void GameMap::setBackgroundTexture(const QString& texturePath)
    { _backgroundTexture = texturePath; }
