#pragma once

#include <QObject>
#include <QTimer>
#include <QSet>
#include <QPointF>

#include "models/gameState.h"



class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameState* gameState READ gameState CONSTANT)
    Q_PROPERTY(bool isGameOver READ isGameOver NOTIFY gameOver)

public:
    explicit GameController(GameState* gameState, QObject* parent = nullptr);
    
    GameState* gameState() const noexcept;
    bool isGameOver() const noexcept;

    Q_INVOKABLE void setKeyState(int qtKey, bool isPressed);
    Q_INVOKABLE void updateMousePosition(qreal x, qreal y);
    Q_INVOKABLE void shoot();

signals:
    void gameOver();

private slots:
    void gameTick();

private:
    void processPlayer(qreal deltaTime);
    void processEnemies(qreal deltaTime);
    void processBullets(qreal deltaTime);

    void spawnEnemies(qreal deltaTime);

    void resolveCollisions(DynamicGameObject* object) const;
    bool resolveBulletWallCollisions(Bullet* bullet) const;

private:
    GameState* _gameState;
    QTimer* _gameLoopTimer;
    QSet<int> _pressedKeys;
    QPointF _mousePos;
    bool _isGameOver;

    qreal _timeSinceLastSpawn = 0.0;
};
