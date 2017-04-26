/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

import Sounder 1.0


Page {
    id: page


    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView

        PullDownMenu {
            /*
            MenuItem {
                text: qsTr("Play guitar notes")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }*/
        }

        Image {
            //source: "head_1.jpg"
            source: "head_3.png"
            fillMode: Image.PreserveAspectFit

            anchors.fill: parent
            z: -1
        }

        Tuner {
            id: tuner

            onNoteChanged: {
                note.text = tuner.note
                note.color = tuner.shift == 0 ? "green" : "red"
                pegManager.updatePegs(tuner.frequency)

                switch(tuner.shift) {
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
                soundLevel.volume = tuner.level

            }

        }

        Text {
            id: note

            width: parent.width/4
            height: parent.height/8

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: "red"
            font.bold: true
            font.pixelSize: Theme.fontSizeExtraLarge * 2
            horizontalAlignment: Text.AlignHCenter
        }

        Arrow {
            id: upperArrow

            upper: true

            width: Math.floor(parent.width * 0.4)
            height: Math.floor(parent.height / 6)

            x: (parent.width-upperArrow.width) / 2
            y: parent.height / 8
        }

        Arrow {
            id: lowerArrow

            upper: false

            width: Math.floor(parent.width * 0.4)
            height: Math.floor(parent.height / 6)

            x: (parent.width - lowerArrow.width) / 2
            y: parent.height - lowerArrow.height - parent.height / 8
        }

        PegManager {
            id: pegManager

            head: parent

            Component.onCompleted: pegManager.addPegs()
        }

        SoundLevel {
            id: soundLevel

            width: parent.width
            height: parent.height * 0.1

            x: 0
            y: parent.height * 0.45

        }
    }
}

