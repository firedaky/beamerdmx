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
import BeamerDMX 1.0

Rectangle {
    width: 640
    height: 480
    color: "black"

    LaserSurface {
        property real pan: 0.0
        property real tilt: 0.0
        property real zoom: 1.0
        property bool shutter: true
        property real dimmer: 1.0
        property real angle: 0.0

        x: ((parent.width - width) / 2)   + pan  * parent.width
        y: ((parent.height - height) / 2) + tilt * parent.height

        width: parent.width
        height: parent.height

        scale: zoom
        rotation: angle
        opacity: dimmer * shutter

        objectName: "LaserSurface"
    }
}
