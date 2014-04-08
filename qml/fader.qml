import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    property real faderValue: 0.0
    property string faderLabel: "Fader"
    property string faderText: "0"
    property color faderBackground: "lightgray"

    signal faderMoved(real newValue)

    Rectangle {
        anchors.fill: parent
        color: faderBackground

        Text {
            id: faderLabelField
            text: faderLabel
            width: parent.width
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            anchors.top: parent.top
        }

        Slider {
            id: faderSlider

            minimumValue: 0.0
            maximumValue: 255.0
            orientation: Qt.Vertical
            stepSize: 1.0
            value: faderValue

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            anchors.top: faderLabelField.bottom
            anchors.bottomMargin: 5
            anchors.bottom: faderTextField.top

            onValueChanged: {
                faderMoved(value)
            }
        }

        Text {
            id: faderTextField
            text: faderText
            width: parent.width
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
            anchors.bottom: parent.bottom
        }
    }
}
