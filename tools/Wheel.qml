import QtQuick 2.0

Rectangle {
    height: 700
    width: 485
    color: "#333333"

    Column {
        anchors.centerIn: parent
        spacing: 2

        Repeater {
            model: ["#9ACD32", "#EEEEEE", "#FFD700", "#87CEEB"]

            Rectangle {
                property real scaleFactor: 1

                height: 40 * scaleFactor
                width: 60 * scaleFactor
                color: modelData
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    anchors.fill: parent
                    onWheel: {
                        if (wheel.modifiers & Qt.ControlModifier) {
                            if (wheel.angleDelta.y > 0)
                                parent.scaleFactor += 0.2;
                            else if (parent.scaleFactor - 0.2 >= 0.2)
                                parent.scaleFactor -= 0.2;
                        }
                    }
                }
            }
        }
    }

    Text {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#FFD700"
        text: "Rotate the mouse wheel pressing <Control> to resize the squares."
    }
}