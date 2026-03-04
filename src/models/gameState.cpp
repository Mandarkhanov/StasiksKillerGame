#include <cmath>

#include "models/gameState.h"



GameState::GameState(const QSize& mapSize, QObject* parent)
    : QObject(parent),
      _gameMap(new GameMap(mapSize, this))
{ }

GameMap* GameState::gameMap() const noexcept
    { return _gameMap; }

Player* GameState::player() const noexcept
    { return _player; }

void GameState::setPlayer(Player* player)
{
    if (_player && _player != player) {
        _player->deleteLater();
    }
    _player = player;
}

EnemyParams GameState::enemyPrototype() const noexcept
    { return _enemyPrototype; }

void GameState::setEnemyPrototype(const EnemyParams& prototype)
    { _enemyPrototype = prototype; }

QList<Enemy*> GameState::enemies() const noexcept
    { return _enemies; }

void GameState::addEnemy(Enemy* enemy)
{
    _enemies.append(enemy);
    emit enemiesChanged();
}

void GameState::removeEnemy(Enemy* enemy)
{
    if (_enemies.removeOne(enemy)) {
        enemy->deleteLater();
        emit enemiesChanged();
    }
}

QList<Bullet*> GameState::bullets() const noexcept
    { return _bullets; }

void GameState::addBullet(Bullet* bullet)
{
    _bullets.append(bullet);
    emit bulletsChanged();
}

void GameState::removeBullet(Bullet* bullet)
{
    if (_bullets.removeOne(bullet)) {
        bullet->deleteLater();
        emit bulletsChanged();
    }
}
