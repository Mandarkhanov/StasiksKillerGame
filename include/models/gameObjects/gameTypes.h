#pragma once

#include <QObject>

namespace GameTypes {
    Q_NAMESPACE
    enum class ObjectType
    {
        Player,
        Enemy,
        Wall,
        Bullet,
        Unknown,
    };
    Q_ENUM_NS(ObjectType)
}
