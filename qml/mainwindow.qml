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

            onFaderMoved: {
                faderText = (newValue / 2.55).toFixed(1) + "%"
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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

            onFaderMoved: {
                if (newValue < 8)
                {
                    faderText = "From file"
                }
                else if (newValue < 16)
                {
                    faderText = "RGB"
                }
                else if (newValue < 24)
                {
                    faderText = "Red"
                }
                else if (newValue < 32)
                {
                    faderText = "Amber"
                }
                else if (newValue < 40)
                {
                    faderText = "Yellow"
                }
                else if (newValue < 48)
                {
                    faderText = "Light Green"
                }
                else if (newValue < 56)
                {
                    faderText = "Green"
                }
                else if (newValue < 64)
                {
                    faderText = "Cyan"
                }
                else if (newValue < 72)
                {
                    faderText = "Light Blue"
                }
                else if (newValue < 80)
                {
                    faderText = "Blue"
                }
                else if (newValue < 88)
                {
                    faderText = "Magenta"
                }
                else if (newValue < 96)
                {
                    faderText = "Pink"
                }
                else if (newValue < 128)
                {
                    faderText = "Open"
                }
                else if (newValue < 192)
                {
                    faderText = "Rainbow >"
                }
                else
                {
                    faderText = "Rainbow <"
                }
            }
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

            onFaderMoved: {
                if (newValue < 8)
                {
                    faderText = "From file"
                }
                else if (newValue < 16)
                {
                    faderText = "RGB"
                }
                else if (newValue < 24)
                {
                    faderText = "Red"
                }
                else if (newValue < 32)
                {
                    faderText = "Amber"
                }
                else if (newValue < 40)
                {
                    faderText = "Yellow"
                }
                else if (newValue < 48)
                {
                    faderText = "Light Green"
                }
                else if (newValue < 56)
                {
                    faderText = "Green"
                }
                else if (newValue < 64)
                {
                    faderText = "Cyan"
                }
                else if (newValue < 72)
                {
                    faderText = "Light Blue"
                }
                else if (newValue < 80)
                {
                    faderText = "Blue"
                }
                else if (newValue < 88)
                {
                    faderText = "Magenta"
                }
                else if (newValue < 96)
                {
                    faderText = "Pink"
                }
                else if (newValue < 128)
                {
                    faderText = "Open"
                }
                else if (newValue < 192)
                {
                    faderText = "Rainbow >"
                }
                else
                {
                    faderText = "Rainbow <"
                }
            }
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

            onFaderMoved: {
                faderText = (newValue / 2.55).toFixed(1) + "%"
            }
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

            onFaderMoved: {
                faderText = (newValue / 2.55).toFixed(1) + "%"
            }
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

            onFaderMoved: {
                faderText = (newValue / 2.55).toFixed(1) + "%"
            }
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

            onFaderMoved: {
                faderText = "Folder " + ((Math.floor((newValue) / 4)) + 1).toFixed(0);
            }
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

            onFaderMoved: {
                var upperHalf = newValue > 128

                if (upperHalf)
                {
                    faderText = "File " + ((Math.floor((newValue - 128) / 4)) + 1).toFixed(0) + " (rotating)"
                }
                else
                {
                    faderText = "File " + ((Math.floor(newValue / 4)) + 1).toFixed(0) + " (indexed)"
                }
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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

            onFaderMoved: {
                faderText = (newValue / 2.55).toFixed(1) + "%"
            }
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

            onFaderMoved: {
                if (newValue < 16)
                {
                    faderText = "Closed";
                }
                else if (newValue < 129)
                {
                    faderText = (((newValue - 16.0) / (128 - 16)) * 9.0 + 1.0).toFixed(2) + " Hz Strobe"
                }
                else if (newValue < 240)
                {
                    faderText = "< " + (((newValue - 129.0) / (239 - 129)) * 9.0 + 1.0).toFixed(2) + " Hz Random"
                }
                else
                {
                    faderText = "Open";
                }
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0) + " BPM"
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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

            onFaderMoved: {
                faderText = newValue.toFixed(0)
            }
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
            width: childrenRect.width + 15
            height: childrenRect.height + 10

            anchors.margins: 5
            anchors.left: parent.left
            anchors.top: parent.top

            color: "lightgray"

            Button {
                id: normalButton

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
                anchors.left: normalButton.right

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
