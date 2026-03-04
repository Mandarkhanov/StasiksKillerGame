#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>

#include "core/stasiksKillerApplication.h"
#include "core/hardcodedLevelBuilder.h"

// #include "models/gameObjects/gameObject.h"
// #include "models/gameObjects/unit.h"
// #include "models/gameObjects/wall.h"
// #include "models/gameObjects/player.h"
// #include "models/gameObjects/enemy.h"

// #include "models/gameMap.h"
// #include "models/gameState.h"
// #include "controllers/gameController.h"



StasiksKillerApplication::StasiksKillerApplication(QObject* parent)
    : QObject(parent)
{
    setupEngine();
}

void StasiksKillerApplication::setupEngine()
{
    qmlRegisterSingletonInstance("StasiksKiller.Core", 1, 0, "GameApp", this);

    _engine.loadFromModule("StasiksKiller", "Main");
}

//     const char* uriModels = "StasiksKiller.Models";
//     const char* uriControllers = "StasiksKiller.Controllers";

//     qmlRegisterType<GameObject>(uriModels, 1, 0, "GameObject");
//     qmlRegisterType<Unit>(uriModels, 1, 0, "Unit");
//     qmlRegisterType<Wall>(uriModels, 1, 0, "Wall");
//     qmlRegisterType<Player>(uriModels, 1, 0, "Player");
//     qmlRegisterType<Enemy>(uriModels, 1, 0, "Enemy");

//     qmlRegisterUncreatableType<GameMap>(uriModels, 1, 0, "GameMap", "GameMap is created by C++");
//     qmlRegisterUncreatableType<GameState>(uriModels, 1, 0, "GameState", "GameState is managed by Controller");
//     qmlRegisterUncreatableType<GameController>("StasiksKiller.Core", 1, 0, "GameController", "Controller is managed by App");

//     _qmlEngine->rootContext()->setContextProperty("StasiksKillerApplication", this);

void StasiksKillerApplication::startNewGame()
{
    if (_activeController) {
        _activeController->deleteLater();
        _activeController = nullptr;
    }

    HardcodedLevelBuilder builder(1);
    GameState* gameState = builder.build(this);
    _activeController = new GameController(gameState, this);

    emit activeControllerChanged();
}

void StasiksKillerApplication::quitGame()
{
    if (_activeController) {
        _activeController->deleteLater();
        _activeController = nullptr;
    }

    emit activeControllerChanged();
}

GameController *StasiksKillerApplication::getActiveController() const noexcept
    { return _activeController; }
