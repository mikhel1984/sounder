import QtQuick 2.0

Item {

    property int diametr: 20

    // range of freqencies and central note
    property double lowBound: 20
    property double upBound: 20000
    property double center: 440

    // current frequency
    property double frequency: 0

    SpriteSequence {
        id: peg

        width: parent.diametr
        height: parent.diametr

        Sprite {
            name: "red"
            source: "marks_red.png"
            frameCount: 1
        }

        Sprite {
            name: "green"
            source: "marks_green.png"
            frameCount: 1
        }

        Sprite {
            name: "none"
            source: "marks_transparent.png"
            frameCount: 1
        }
    }

    onFrequencyChanged: {
        if(Math.abs(frequency-center) < 1) {
            peg.jumpTo("green")
        }
        else if((frequency > lowBound && frequency < center) || (frequency > center && frequency <= upBound)) {
            peg.jumpTo("red")
        }
        else {
            peg.jumpTo("none")
        }
    }


}
