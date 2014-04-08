//   Copyright 2014 Lukas Erlinghagen

//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//       http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id: page
    width: 1280; height: 800
    color: "lightgray"

    Rectangle {
        id: channelView

        anchors.margins: 5
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: buttons.top

        color: "gray"

        Fader {
            id: faderDimmer
            objectName: "faderDimmer"
            faderLabel: "Dimmer"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }

        Fader {
            id: faderPan
            objectName: "faderPan"
            faderLabel: "Pan (coarse)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderDimmer.right
        }

        Fader {
            id: faderTilt
            objectName: "faderTilt"
            faderLabel: "Tilt (coarse)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderPan.right
        }

        Fader {
            id: faderColor1
            objectName: "faderColor1"
            faderLabel: "Color 1"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderTilt.right
        }

        Fader {
            id: faderColor2
            objectName: "faderColor2"
            faderLabel: "Color 2"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderColor1.right
        }

        Fader {
            id: faderRed
            objectName: "faderRed"
            faderLabel: "Red"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderColor2.right
        }

        Fader {
            id: faderGreen
            objectName: "faderGreen"
            faderLabel: "Green"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderRed.right
        }

        Fader {
            id: faderBlue
            objectName: "faderBlue"
            faderLabel: "Blue"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderGreen.right
        }

        Fader {
            id: faderFolder
            objectName: "faderFolder"
            faderLabel: "Folder"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderBlue.right
        }

        Fader {
            id: faderFile
            objectName: "faderFile"
            faderLabel: "File"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderFolder.right
        }

        Fader {
            id: faderRotation
            objectName: "faderRotation"
            faderLabel: "Rotation (coarse)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderFile.right
        }

        Fader {
            id: faderZoom
            objectName: "faderZoom"
            faderLabel: "Zoom"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderRotation.right
        }

        Fader {
            id: faderStrobe
            objectName: "faderStrobe"
            faderLabel: "Strobe"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left:faderZoom.right
        }

        Fader {
            id: faderBpm
            objectName: "faderBpm"
            faderLabel: "BPM"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderStrobe.right
        }

        Fader {
            id: faderPanFine
            objectName: "faderPanFine"
            faderLabel: "Pan (fine)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderBpm.right
        }

        Fader {
            id: faderTiltFine
            objectName: "faderTiltFine"
            faderLabel: "Tilt (fine)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderPanFine.right
        }

        Fader {
            id: faderRotationFine
            objectName: "faderRotationFine"
            faderLabel: "Rotation (fine)"
            faderValue: 0.0

            width: ((parent.width - 18 * 5) / 17)

            anchors.margins: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: faderTiltFine.right
        }
    }

    Rectangle {
        id: buttons

        height: 150

        anchors.margins: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "darkgray"

        Button {
            anchors.margins: 5
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            text: "Quit"

            onClicked: {
                Qt.quit();
            }
        }
    }
}
