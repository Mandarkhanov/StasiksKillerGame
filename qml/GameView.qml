import QtQuick
import QtQuick.Controls
import StasiksKiller.Core 1.0

Rectangle {
    id: root
    color: "#2C3E50"
    focus: !GameApp.activeController.isGameOver

    property real mouseXPos: 0
    property real mouseYPos: 0

    Keys.onPressed: (event) => {
        if (event.isAutoRepeat) return;

        if (GameApp.activeController) {
            GameApp.activeController.setKeyState(event.key, true);
        }
        event.accepted = true;
    }

    Keys.onReleased: (event) => {
        if (event.isAutoRepeat) return;

        if (GameApp.activeController) {
            GameApp.activeController.setKeyState(event.key, false);
        }
        event.accepted = true;
    }

    Image {
        id: gameWorld
        width: GameApp.activeController.gameState.gameMap.size.width
        height: GameApp.activeController.gameState.gameMap.size.height
        anchors.centerIn: parent

        source: GameApp.activeController.gameState.gameMap.backgroundTexture
        fillMode: Image.Tile

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.BlankCursor

            onPositionChanged: (mouse) => {
                root.mouseXPos = mouse.x;
                root.mouseYPos = mouse.y;

                if (GameApp.activeController && !GameApp.activeController.isGameOver) {
                    GameApp.activeController.updateMousePosition(mouse.x, mouse.y);
                }
            }

            onClicked: (mouse) => {
                if (GameApp.activeController && !GameApp.activeController.isGameOver) {
                    GameApp.activeController.shoot();
                }
            }
        }

        Repeater {
            model: GameApp.activeController.gameState.gameMap.walls
            delegate: Image {
                x: modelData.position.x
                y: modelData.position.y
                width: modelData.size.width
                height: modelData.size.height

                source: modelData.texturePath
                fillMode: Image.Tile
            }
        }

        Repeater {
            model: GameApp.activeController.gameState.bullets
            delegate: Bullet {
                bulletData: modelData
                z : 1
            }
        }

        Repeater {
            model: GameApp.activeController.gameState.enemies
            delegate: Enemy {
                enemyData: modelData
                z: 2
            }
        }

        Player {
            player: GameApp.activeController.gameState.player
            z: 3
        }

        Item {
            id: crosshair
            width: 30
            height: 30
            z: 10

            x: root.mouseXPos - width / 2;
            y: root.mouseYPos - width / 2;

            visible: GameApp.activeController ? !GameApp.activeController.isGameOver : false

            // Центральная точка
            Rectangle {
                width: 4
                height: 4
                color: "red"
                radius: 2
                anchors.centerIn: parent
            }

            // Внешний круг
            Rectangle {
                width: parent.width
                height: parent.height
                color: "transparent"
                border.color: "red"
                border.width: 2
                radius: width / 2
                opacity: 0.7
            }

            // Верхняя риска
            Rectangle {
                width: 2; height: 8
                color: "red"
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
            // Нижняя риска
            Rectangle {
                width: 2; height: 8
                color: "red"
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
            // Левая риска
            Rectangle {
                width: 8; height: 2
                color: "red"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
            // Правая риска
            Rectangle {
                width: 8; height: 2
                color: "red"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20

        text: "СЧЕТ: " + (GameApp.activeController ? GameApp.activeController.gameState.player.exp : 0)

        color: "white"
        font.pixelSize: 48
        font.bold: true
        style: Text.Outline
        styleColor: "black"

        visible: GameApp.activeController ? !GameApp.activeController.isGameOver : false
        z: 5
    }

    Rectangle {
        id: gameOverOverlay
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.7)

        visible: GameApp.activeController ? GameApp.activeController.isGameOver : false
        z: 10

        Column {
            anchors.centerIn: parent
            spacing: 30

            Text {
                text: "ВАС СЪЕЛ СТАСИК!"
                color: "red"
                font.pixelSize: 64
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                text: "НАБРАНО ОЧКОВ: " + (GameApp.activeController ? GameApp.activeController.gameState.player.exp : 0)
                color: "white"
                font.pixelSize: 32
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                text: "В Главное Меню"
                width: 250
                height: 70
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 24

                onClicked: {
                    GameApp.quitGame()
                }
            }
        }

    }
}
