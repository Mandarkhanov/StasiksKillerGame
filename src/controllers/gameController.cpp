#include "controllers/gameController.h"

#include <random>
#include <QVector2D>
#include <QtMath>



namespace {
    constexpr int GAME_TICK_INTERVAL_MS = 16;
    constexpr qreal DELTA_TIME_S = GAME_TICK_INTERVAL_MS / 1000.0;

    constexpr qreal MATH_EPSILON = 1.0e-6;
    inline bool isColliding(DynamicGameObject* a, DynamicGameObject* b)
    {
        if (!a || !b) {
            return false;
        }
        QVector2D diff(a->position() - b->position());
        return diff.length() - (a->radius() + b->radius()) <= MATH_EPSILON;
    }
}

GameController::GameController(GameState* gameState, QObject* parent)
    : QObject(parent),
      _gameState(gameState),
      _gameLoopTimer(new QTimer(this)),
      _isGameOver(false)
{
    connect(_gameLoopTimer, &QTimer::timeout, this, &GameController::gameTick);

    _gameLoopTimer->start(GAME_TICK_INTERVAL_MS);
}

void GameController::gameTick()
{
    _timeSinceLastSpawn += DELTA_TIME_S;

    processPlayer(DELTA_TIME_S);
    processEnemies(DELTA_TIME_S);
    processBullets(DELTA_TIME_S);
    spawnEnemies(DELTA_TIME_S);
}

void GameController::processPlayer(qreal deltaTime)
{
    Player* player = _gameState->player();
    if (!player) {
        return;
    }

    QVector2D movementVector(0.0f, 0.0f);
    if (_pressedKeys.contains(Qt::Key_W)) movementVector.setY(movementVector.y() - 1.0f);
    if (_pressedKeys.contains(Qt::Key_A)) movementVector.setX(movementVector.x() - 1.0f);
    if (_pressedKeys.contains(Qt::Key_S)) movementVector.setY(movementVector.y() + 1.0f);
    if (_pressedKeys.contains(Qt::Key_D)) movementVector.setX(movementVector.x() + 1.0f);
    if (!movementVector.isNull()) {
        movementVector.normalize();
    }
    player->setVelocity(movementVector * player->speed());
    player->updatePosition(DELTA_TIME_S);
    resolveCollisions(player);

    QVector2D toMouse(_mousePos - player->position());
    if (!toMouse.isNull()) {
        qreal angle = qRadiansToDegrees(qAtan2(toMouse.y(), toMouse.x()));
        player->setRotation(angle);
    }
}

void GameController::processEnemies(qreal deltaTime)
{
    Player* player = _gameState->player();
    if (!player) {
        return;
    }

    QList<Enemy*> enemies = _gameState->enemies();
    for (Enemy* enemy : enemies) {
        QVector2D direction(player->position() - enemy->position());
        if (!direction.isNull()) {
            direction.normalize();
            qreal angle = qRadiansToDegrees(qAtan2(direction.y(), direction.x()));
            enemy->setRotation(angle);
        }

        enemy->setVelocity(direction * enemy->speed());
        enemy->updatePosition(DELTA_TIME_S);
        resolveCollisions(enemy);

        if (isColliding(player, enemy)) {
            _gameLoopTimer->stop();
            _isGameOver = true;
            emit gameOver();
            return;
        }
    }

    for (int i = 0; i < enemies.size(); ++i) {
        for (int j = i + 1; j < enemies.size(); ++j) {
            Enemy* e1 = enemies[i];
            Enemy* e2 = enemies[j];

            QVector2D diff(e1->position() - e2->position());
            qreal dist = diff.length();
            qreal sumR = e1->radius() + e2->radius();

            if (dist < sumR && dist > MATH_EPSILON) {
                qreal overlap = sumR - dist;
                diff.normalize();

                QPointF pushVector = (diff * (overlap * 0.5)).toPointF();
                e1->setPosition(e1->position() + pushVector);
                e2->setPosition(e2->position() - pushVector);
            }
        }
    }
}

void GameController::processBullets(qreal deltaTime)
{
    QList<Bullet*> bullets = _gameState->bullets();
    QList<Enemy*> enemies = _gameState->enemies();

    for (Bullet* bullet : bullets) {
        bullet->updatePosition(deltaTime);

        if (resolveBulletWallCollisions(bullet)) {
            _gameState->removeBullet(bullet);
            continue;
        }

        bool hitEnemy = false;
        for (Enemy* enemy : enemies) {
            if (isColliding(bullet, enemy)) {
                _gameState->removeBullet(bullet);

                enemy->takeDamage(bullet->damage());
                if (enemy->hp() <= 0) {
                    _gameState->removeEnemy(enemy);
                    if (Player* player = _gameState->player(); player) {
                        player->addExp(10.0);
                    }
                }

                hitEnemy = true;
                break;
            }
        }
        if (hitEnemy) {
            continue;
        }
    }
}

void GameController::spawnEnemies(qreal deltaTime)
{
    if (_isGameOver) {
        return;
    }

    constexpr qreal SPAWN_INTERNAL = 0.5;
    constexpr int MAX_ENEMIES_N = 25;

    if (_timeSinceLastSpawn >= SPAWN_INTERNAL && _gameState->enemies().size() < MAX_ENEMIES_N) {
        QSize mapSize = _gameState->gameMap()->size();
        qreal w = mapSize.width();
        qreal h = mapSize.height();

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<> sideDist(0, 3);
        int side = sideDist(gen);

        QPointF spawnPos;
        qreal margin = 10.0;
        std::uniform_real_distribution<qreal> xDist(margin, w - margin);
        std::uniform_real_distribution<qreal> yDist(margin, h - margin);

        if (side == 0)      spawnPos = QPointF(xDist(gen), margin);
        else if (side == 1) spawnPos = QPointF(w - margin, yDist(gen));
        else if (side == 2) spawnPos = QPointF(xDist(gen), h - margin);
        else                spawnPos = QPointF(margin, yDist(gen));

        EnemyParams eParams = _gameState->enemyPrototype();
        eParams.position = spawnPos;

        std::uniform_real_distribution<qreal> scaleDist(0.7, 1.5);
        qreal scaleFactor = scaleDist(gen);
        eParams.radius *= scaleFactor;
        eParams.hp *= scaleFactor;
        eParams.speed /= scaleFactor;

        _gameState->addEnemy(new Enemy(eParams, _gameState));
        _timeSinceLastSpawn = 0.0;
    }
}

void GameController::shoot()
{
    Player* player = _gameState->player();
    if (!player || _isGameOver) {
        return;
    }

    QVector2D direction(_mousePos - player->gunPos());
    if (direction.isNull()) {
        return;
    }
    direction.normalize();

    BulletParams bParams;
    bParams.type = GameTypes::ObjectType::Bullet;
    bParams.position = player->gunPos();
    bParams.radius = 4.0;

    qreal bulletSpeed = 800.0;
    bParams.velocity = direction * bulletSpeed;

    bParams.damage = 15.0;
    bParams.rotation = qRadiansToDegrees(qAtan2(direction.y(), direction.x()));

    _gameState->addBullet(new Bullet(bParams, _gameState));
}

void GameController::resolveCollisions(DynamicGameObject* object) const
{
    if (!object || !_gameState->gameMap()) {
        return;
    }

    QPointF pos = object->position();
    qreal r = object->radius();

    for (Wall* w : _gameState->gameMap()->walls()) {
        QRectF rect = w->rect();

        qreal closestX = std::clamp(pos.x(), rect.left(), rect.right());
        qreal closestY = std::clamp(pos.y(), rect.top(), rect.bottom());

        qreal dx = pos.x() - closestX;
        qreal dy = pos.y() - closestY;

        qreal distanceSquared = dx * dx + dy * dy;

        if ((distanceSquared - r * r) < MATH_EPSILON) {
            qreal distance = std::sqrt(distanceSquared);

            bool inside = distance < MATH_EPSILON;
            if (inside) {
                qreal dLeft = std::abs(pos.x() - rect.left());
                qreal dRight = std::abs(pos.x() - rect.right());
                qreal dTop = std::abs(pos.y() - rect.top());
                qreal dBottom = std::abs(pos.y() - rect.bottom());

                qreal minX = std::min(dLeft, dRight);
                qreal minY = std::min(dTop, dBottom);

                if (minX < minY) {
                    if (dLeft < dRight) pos.setX(rect.left() - r);
                    else                pos.setX(rect.right() + r);
                } else {
                    if (dTop < dBottom) pos.setY(rect.top() - r);
                    else                pos.setY(rect.bottom() + r);
                }
            } else {
                qreal overlap = r - distance;
                qreal nx = dx / distance;
                qreal ny = dy / distance;

                pos.setX(pos.x() + nx * overlap);
                pos.setY(pos.y() + ny * overlap);
            }
        }
    }
    object->setPosition(pos);
}

bool GameController::resolveBulletWallCollisions(Bullet* bullet) const
{
    QPointF pos = bullet->position();
    qreal r = bullet->radius();

    for (Wall* w : _gameState->gameMap()->walls()) {
        QRectF rect = w->rect();

        qreal closestX = std::clamp(pos.x(), rect.left(), rect.right());
        qreal closestY = std::clamp(pos.y(), rect.top(), rect.bottom());
        qreal dx = pos.x() - closestX;
        qreal dy = pos.y() - closestY;

        if ((dx * dx + dy * dy) < r * r) {
            return true;
        }
    }
    return false;
}

void GameController::setKeyState(int qtKey, bool isPressed)
{
    if (isPressed) {
        _pressedKeys.insert(qtKey);
    } else {
        _pressedKeys.remove(qtKey);
    }
}

void GameController::updateMousePosition(qreal x, qreal y)
    { _mousePos = QPointF(x, y); }

GameState* GameController::gameState() const noexcept
    { return _gameState; }

bool GameController::isGameOver() const noexcept
    { return _isGameOver; }
