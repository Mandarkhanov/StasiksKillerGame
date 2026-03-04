#pragma once

#include <QObject>
#include "models/gameState.h"

class ILevelBuilder
{
public:
    virtual GameState* build(QObject* parent = nullptr) = 0;
    virtual ~ILevelBuilder() = default;
};
