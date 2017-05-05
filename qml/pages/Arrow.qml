import QtQuick 2.0

Item {
    // Arrows show the direction of frequency changing
    // to get accurate note

    property bool upper: true       // upper or lower arrow relative to text label
    property bool signaling: false  // should the arrow be active (red)

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
        // change state
        if(signaling)
            arrow.jumpTo("signal")
        else
            arrow.jumpTo("calm")
    }


}
