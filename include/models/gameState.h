#pragma once

#include <QObject>

#include "models/gameMap.h"
#include "models/gameObjects/player.h"
#include "models/gameObjects/enemy.h"
#include "models/gameObjects/bullet.h"

class DynamicGameObject;



class GameState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameMap* gameMap READ gameMap CONSTANT)
    Q_PROPERTY(Player* player READ player CONSTANT)
    Q_PROPERTY(QList<Enemy*> enemies READ enemies NOTIFY enemiesChanged)
    Q_PROPERTY(QList<Bullet*> bullets READ bullets NOTIFY bulletsChanged)

public:
    explicit GameState(const QSize& mapSize, QObject* parent = nullptr);

    GameMap* gameMap() const noexcept;

    Player* player() const noexcept;
    void setPlayer(Player* player);

    EnemyParams enemyPrototype() const noexcept;
    void setEnemyPrototype(const EnemyParams& prototype);
    QList<Enemy*> enemies() const noexcept;
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);

    QList<Bullet*> bullets() const noexcept;
    void addBullet(Bullet* bullet);
    void removeBullet(Bullet* bullet);

signals:
    void enemiesChanged();
    void bulletsChanged();

private:
    GameMap* _gameMap;
    Player* _player = nullptr;
    QList<Enemy*> _enemies;
    QList<Bullet*> _bullets;
    EnemyParams _enemyPrototype;
};
