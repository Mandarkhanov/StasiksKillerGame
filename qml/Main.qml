import QtQuick
import QtQuick.Window
import StasiksKiller.Core 1.0

Window {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: "StasiksKiller"

    // Для расположения окна посередине главного экрана
    screen: Qt.application.screens[0]
    Component.onCompleted: {
        setX(screen.virtualX + (screen.width - width) / 2)
        setY(screen.virtualY + (screen.height - height) / 2)
    }

    Loader {
        id : screenLoader
        anchors.fill: parent
        source: GameApp.activeController ? "GameView.qml" : "MainMenu.qml"
    }
}
