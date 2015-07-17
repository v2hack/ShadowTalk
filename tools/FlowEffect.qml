import QtQuick 2.0
Rectangle {
    width: 800; height: 480
    color: "black"
    Component.onCompleted: animation.start()
    Flow {
        id: flow
        property real originalWidth: 790
        x: 5; y: 5
        width: originalWidth
        spacing: 10
        Repeater {
            id: repeater
            model: 104
            Rectangle {
                width: 20; height: 20
                color: { var c = index / repeater.count; return Qt.rgba(1-c, c, c, 1) }
            }
        }
    }
    SequentialAnimation {
        id: animation
        loops: Animation.Infinite
        PropertyAnimation { target: flow; property: "width"; to: 200; duration: 1000 }
        PropertyAnimation { target: flow; property: "width"; to: flow.originalWidth; duration: 1000 }
    }
}