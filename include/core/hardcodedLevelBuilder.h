#pragma once

#include "core/iLevelBuilder.h"

class HardcodedLevelBuilder : public ILevelBuilder
{
public:
    explicit HardcodedLevelBuilder(int levelId);

    GameState* build(QObject* parent = nullptr) override;

private:
    GameState* buildLevel1(QObject* parent);

private:
    int _levelId;
};
