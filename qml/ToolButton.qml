import QtQuick 2.4

Item {
    id: button

    property alias background: background.source
    property bool stateless: true
    property bool active: false // useless in stateless mode
    property bool pressed: stateless ? trap.pressed : active
    property alias description: bubble.text
    signal clicked(variant mouse)

    width: background.width
    height: width

    MouseArea {
        id: trap
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            active ^= true
            button.clicked(mouse)
        }
    }

    states: [
        State {
            name: "hovered"
            when: trap.containsMouse && !pressed
            PropertyChanges {
                target: hoverEffect
                opacity: 1
            }
            PropertyChanges {
                target: bubble
//                opacity: 0.8
            }
        },
        State {
            name: "pressed"
            when: stateless && pressed
            PropertyChanges {
                target: stop1
                color: "black"
            }
            PropertyChanges {
                target: stop3
                color: "black"
            }
        },
        State {
            name: "active"
            when: !stateless && active
            PropertyChanges {
                target: hoverEffect
                opacity: 1
            }
            PropertyChanges {
                target: hoverEffect
                opacity: 1
            }
            PropertyChanges {
                target: stop1
                color: "white"
            }
        }

    ]

    transitions: Transition {
        NumberAnimation {
            target: hoverEffect
            property: "opacity"
            duration: 250
        }
        NumberAnimation {
            target: bubble
            property: "opacity"
            duration: 100
        }
    }

    Rectangle {
        id: hoverEffect
        anchors.fill: parent
        anchors.margins: 3
        gradient: Gradient {
            GradientStop { id: stop1; position: 0.0; color: "transparent" }
            GradientStop { id: stop2; position: 0.5; color: "white" }
            GradientStop { id: stop3; position: 1.0; color: "transparent" }
        }
        rotation: 90
        opacity: 0
    }

    Image {
        id: background
        sourceSize.width: 30
        sourceSize.height: 30
        smooth: true
        opacity: 0.6
    }

//    TextBubble {
//        id: bubble
//        anchors {
//            top: background.top
//            bottom: background.bottom
//            left: background.right
//            leftMargin: 10
//        }
//        opacity: 0.0
//    }

}
