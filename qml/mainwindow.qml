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

    signal desktopSelectionChanged(real newDesktopId)
    signal showLaserFullscreen
    signal showLaserNormal

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
            objectName: "FaderDimmer"
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
            objectName: "FaderPan"
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
            objectName: "FaderTilt"
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
            objectName: "FaderColor1"
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
            objectName: "FaderColor2"
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
            objectName: "FaderRed"
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
            objectName: "FaderGreen"
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
            objectName: "FaderBlue"
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
            objectName: "FaderFolder"
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
            objectName: "FaderFile"
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
            objectName: "FaderRotation"
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
            objectName: "FaderZoom"
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
            objectName: "FaderStrobe"
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
            objectName: "FaderBpm"
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
            objectName: "FaderPanFine"
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
            objectName: "FaderTiltFine"
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
            objectName: "FaderRotationFine"
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

        Rectangle {
            id: fullscreenButtons
            width: childrenRect.width
            height: childrenRect.height + 10

            anchors.margins: 5
            anchors.left: parent.left
            anchors.top: parent.top

            color: "lightgray"

            Button {
                anchors.margins: 5
                anchors.top: parent.top
                anchors.left: parent.left

                text: "Show normal"

                onClicked: {
                    showLaserNormal()
                }
            }

            Button {
                anchors.margins: 5
                anchors.top: parent.top
                anchors.right: parent.right

                text: "Show fullscreen"

                onClicked: {
                    showLaserFullscreen()
                }
            }
        }

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
