import QtQuick

Item {
    id: root
    property var bulletData

    width: bulletData.radius * 2.0
    height: bulletData.radius * 2.0
    x: bulletData.position.x - width / 2
    y: bulletData.position.y - height / 2
    rotation: bulletData.rotation

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "black"
        border.color: "orange"
        border.width: 1
    }
}
