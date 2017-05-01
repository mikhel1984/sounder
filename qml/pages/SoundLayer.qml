import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    id: layer

    property var head: null
    property var source: null

    property double frequency: source.frequency

    Text {
        id: note

        width: head.width/4
        height: head.height/8

        //anchors.verticalCenter: head.verticalCenter
        //anchors.horizontalCenter: head.horizontalCenter
        //anchors.centerIn: parent
        x: (head.width - note.width) * 0.5
        y: (head.height - note.height) * 0.5

        color: "red"
        font.bold: true
        font.pixelSize: Theme.fontSizeExtraLarge * 2
        horizontalAlignment: Text.AlignHCenter
    }

    Arrow {
        id: upperArrow

        upper: true

        width: Math.floor(head.width * 0.4)
        height: Math.floor(head.height / 6)

        x: (head.width-upperArrow.width) / 2
        y: head.height / 8
    }

    Arrow {
        id: lowerArrow

        upper: false

        width: Math.floor(head.width * 0.4)
        height: Math.floor(head.height / 6)

        x: (head.width - lowerArrow.width) / 2
        y: head.height - lowerArrow.height - head.height / 8
    }

    SoundLevel {
        id: soundLevel

        width: head.width
        height: head.height * 0.1

        x: 0
        y: head.height * 0.45

        volume: source.level

    }

    onFrequencyChanged: {
        note.text = source.note
        note.color = (source.shift == 0) ? "green" : "red"
        //console.log(frequency)

        switch(source.shift) {
        case -1:
            upperArrow.signaling = false
            lowerArrow.signaling = true
            break;
        case 0:
            upperArrow.signaling = false
            lowerArrow.signaling = false
            break;
        case 1:
            upperArrow.signaling = true
            lowerArrow.signaling = false
            break;
        }
    }

}
