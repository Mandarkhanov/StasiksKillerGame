import QtQuick

Item {
    id: root
    property var player
    width: player.radius * 2.0 * player.visualScale
    height: player.radius * 2.0 * player.visualScale
    x: player.position.x - width / 2
    y: player.position.y - height / 2
    rotation: player.rotation

    Image {
        anchors.fill: parent
        source: player.texturePath
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: "blue"
        border.width: 2
    }

    Rectangle {
        width: player.radius * 2.0
        height: player.radius * 2.0
        anchors.centerIn: parent
        radius: width / 2
        color: "transparent"
        border.color: "lime"
        border.width: 2
    }
}
