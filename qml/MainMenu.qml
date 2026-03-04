import QtQuick
import QtQuick.Controls
import StasiksKiller.Core 1.0

Rectangle {
    color: "#2C3E50"

    Text {
        text: "Stasik's Killer"
        color: "white"
        font.pixelSize: 64
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 100
    }

    Button {
        text: "Начать Игру"
        width: 200
        height: 60
        anchors.centerIn: parent
        font.pixelSize: 24

        onClicked: {
            GameApp.startNewGame()
        }
    }
}
