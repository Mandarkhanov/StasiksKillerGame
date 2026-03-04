#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "controllers/gameController.h"



class StasiksKillerApplication : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameController* activeController READ getActiveController  NOTIFY activeControllerChanged)
public:
    explicit StasiksKillerApplication(QObject* parent = nullptr);

    Q_INVOKABLE void startNewGame();
    Q_INVOKABLE void quitGame();

    GameController* getActiveController() const noexcept;

signals:
    void activeControllerChanged();

private:
    void setupEngine();

private:
    QQmlApplicationEngine _engine;

    GameController* _activeController = nullptr;
};
