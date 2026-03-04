cmake_minimum_required(VERSION 3.16)

project(StasiksKiller VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appStasiksKiller
    src/main.cpp
)

qt_add_qml_module(appStasiksKiller
    URI StasiksKiller

    RESOURCES
        assets/Wall.png
        assets/Wood.png
        assets/Stasik.png
        assets/Player.png

    SOURCES
        include/core/stasiksKillerApplication.h
        src/core/stasiksKillerApplication.cpp
        include/core/iLevelBuilder.h
        include/core/hardcodedLevelBuilder.h
        src/core/hardcodedLevelBuilder.cpp

        src/controllers/gameController.cpp
        include/controllers/gameController.h

        src/models/gameMap.cpp
        include/models/gameMap.h
        src/models/gameState.cpp
        include/models/gameState.h
        include/models/gameObjects/gameTypes.h
        include/models/gameObjects/gameObject.h
        src/models/gameObjects/gameObject.cpp
        src/models/gameObjects/wall.cpp
        include/models/gameObjects/wall.h
        include/models/gameObjects/dynamicGameObject.h
        src/models/gameObjects/dynamicGameObject.cpp
        include/models/gameObjects/unit.h
        src/models/gameObjects/unit.cpp
        src/models/gameObjects/player.cpp
        include/models/gameObjects/player.h
        src/models/gameObjects/enemy.cpp
        include/models/gameObjects/enemy.h
        include/models/gameObjects/bullet.h
        src/models/gameObjects/bullet.cpp

    QML_FILES
        qml/Main.qml

        qml/MainMenu.qml
        qml/GameView.qml

        qml/Enemy.qml
        qml/Player.qml
        qml/Bullet.qml
)

target_include_directories(appStasiksKiller
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(appStasiksKiller PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
    WIN32_EXECUTABLE FALSE # для отладки
)

target_link_libraries(appStasiksKiller
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appStasiksKiller
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
