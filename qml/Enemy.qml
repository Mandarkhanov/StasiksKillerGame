import QtQuick

Item {
    id: root
    property var enemyData
    width: enemyData.radius * 2.0 * enemyData.visualScale
    height: enemyData.radius * 2.0 * enemyData.visualScale
    x: enemyData.position.x - width / 2
    y: enemyData.position.y - height / 2
    rotation: enemyData.rotation

    Image {
        anchors.fill: parent
        source: enemyData.texturePath
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: "blue"
        border.width: 2
    }

    Rectangle {
        width: enemyData.radius * 2.0
        height: enemyData.radius * 2.0
        anchors.centerIn: parent
        radius: width / 2
        color: "transparent"
        border.color: "red"
        border.width: 2
    }
}
