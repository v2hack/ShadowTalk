import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

Item {
    property alias leftLabel: buttonLeft.label
    property alias rightLabel: buttonRight.label

    signal leftClicked()
    signal rightClicked()

    anchors.left: parent.left
    anchors.right: parent.right
    height: childrenRect.height

    Button {
        id: buttonLeft
        anchors {
            rightMargin: 5
            right: parent.horizontalCenter
            left: parent.left
        }
        text: "Cancel"
        onClicked: leftClicked()
    }

    Button {
        id: buttonRight
        anchors {
            left: parent.horizontalCenter
            leftMargin: 5
            right: parent.right
        }
        text: "Apply"
        onClicked: rightClicked()
    }
}
