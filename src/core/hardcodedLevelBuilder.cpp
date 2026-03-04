#include "core/hardcodedLevelBuilder.h"



HardcodedLevelBuilder::HardcodedLevelBuilder(int levelId)
    : _levelId(levelId)
{ }

GameState* HardcodedLevelBuilder::build(QObject* parent)
{
    if (_levelId == 1) {
        return buildLevel1(parent);
    }

    return new GameState(QSize(800, 600), parent);
}

GameState* HardcodedLevelBuilder::buildLevel1(QObject* parent)
{
    QSize mapSize(1000, 500);
    GameState* gameState = new GameState(mapSize, parent);
    qreal w = mapSize.width();
    qreal h = mapSize.height();

    GameMap* map = gameState->gameMap();
    map->setBackgroundTexture("qrc:/qt/qml/StasiksKiller/assets/Wood.png");

    qreal wallThick = 10.0;
    QString wallTexture = "qrc:/qt/qml/StasiksKiller/assets/Wall.png";
    auto createWall = [&](const QRectF& rect) {
        WallParams wParams;
        wParams.type = GameTypes::ObjectType::Wall;
        wParams.position = rect.topLeft();
        wParams.size = rect.size();
        wParams.texturePath = wallTexture;
        map->addWall(new Wall(wParams, map));
    };
    createWall(QRectF(0.0, 0.0, w, wallThick));
    createWall(QRectF(0.0, h - wallThick, w, wallThick));
    createWall(QRectF(0.0, wallThick, wallThick, h - 2.0 * wallThick));
    createWall(QRectF(w - wallThick, wallThick, wallThick, h - 2.0 * wallThick));



    PlayerParams pParams;
    pParams.type = GameTypes::ObjectType::Player;
    pParams.position = {w * 0.5, h * 0.5};
    pParams.rotation = 0.0;
    pParams.radius = 40.0;
    pParams.visualScale = 2.0;

    qreal r = pParams.radius * pParams.visualScale;
    pParams.localGunOffset.setX(r);
    pParams.localGunOffset.setY(r * 0.3);

    pParams.speed = 300.0;
    pParams.hp = 100;
    pParams.texturePath = "qrc:/qt/qml/StasiksKiller/assets/Player.png";
    gameState->setPlayer(new Player(pParams, gameState));

    EnemyParams defaultEnemy;
    defaultEnemy.type = GameTypes::ObjectType::Enemy;
    defaultEnemy.radius = 20.0;
    defaultEnemy.speed = 50.0;
    defaultEnemy.hp = 20.0;
    defaultEnemy.targetRadius = 200.0;
    defaultEnemy.texturePath = "qrc:/qt/qml/StasiksKiller/assets/Stasik.png";
    defaultEnemy.visualScale = 2.0;
    gameState->setEnemyPrototype(defaultEnemy);

    return gameState;
}
