import QtQuick 2.0

Item {

    property var head: null

    property var pegs: []

    property int strings: 6

    // generate and setup pegs according to image
    function addPegs() {
        var diametr = Math.floor(head.width / 5)
        var x_shift = head.width * 0.03

        var f_bound = 0
        var component = Qt.createComponent("Peg.qml")

        for(var i = 0; i < strings; i++) {
            var x = i < strings*0.5 ? Math.floor(x_shift) : Math.floor(head.width - x_shift - diametr)
            var k = i < strings*0.5 ? i : (strings-1-i)
            // this magic numbers are used for adjusting circles according to image
            var y = Math.floor(head.height * 0.52 - 1.51*k*diametr)

            var sprite = component.createObject(head, {"x":x, "y":y, "diametr":diametr})

            var f_center = centerFrequency(i)

            sprite.center = f_center
            sprite.lowBound = f_bound

            f_bound = f_center * Math.pow(2, 2.0/12)
            sprite.upBound = i < (strings-1) ? f_bound : 10000

            pegs.push(sprite)
        }
    }

    function updatePegs(freq) {
        pegs.forEach(function(p) {
            p.frequency = freq
        })

    }

    // main frequency for each string
    function centerFrequency(n) {
        var freq = 65.41
        switch(n) {
        case 0:  // E
            freq *= Math.pow(2, 4.0/12)
            break;
        case 1:  // A
            freq *= Math.pow(2, 9.0/12)
            break;
        case 2:  // D
            freq *= Math.pow(2, 14.0/12)
            break;
        case 3:  // G
            freq *= Math.pow(2, 19.0/12)
            break;
        case 4:  // B
            freq *= Math.pow(2, 23.0/12)
            break;
        default:  // E
            freq *= Math.pow(2, 28.0/12)
            break;
        }
        return freq
    }

}
