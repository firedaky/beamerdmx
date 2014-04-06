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
    width: 800; height: 600
    color: "lightgray"

    Rectangle {
        id: channelView

        anchors.margins: 5
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: buttons.top

        color: "gray"
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
