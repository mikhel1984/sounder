import QtQuick 2.0

Item {
    id: level

    property int levelWidth: Math.round(level.width * 0.7)
    property int levelHeight: Math.round(level.height * 0.3)

    property double volume: 1

    Rectangle {
        id: background

        color: "white"
        x: level.x + (level.width-levelWidth)*0.5
        y: level.y + (level.height-levelHeight)*0.5
        width: levelWidth
        height: levelHeight
    }

    Rectangle {
        id: line

        color: "red"
        x: level.x + (level.width-levelWidth)*0.5
        y: level.y + (level.height-levelHeight)*0.5
        z: 1
        height: levelHeight
        width: levelWidth * volume

    }

}
