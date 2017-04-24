import QtQuick 2.0

Item {

    property bool upper: true

    property bool signaling: false

    SpriteSequence {
        id: arrow

        width: parent.width
        height: parent.height

        Sprite {
            name: "signal"
            source: upper ? "arrow_red_d.png" : "arrow_red.png"
            frameCount: 1
        }

        Sprite {
            name: "calm"
            source: upper ? "arrow_transparent_d.png" : "arrow_transparent.png"
            frameCount: 1
        }
    }

    onSignalingChanged: {
        if(signaling)
            arrow.jumpTo("signal")
        else
            arrow.jumpTo("calm")
    }


}
