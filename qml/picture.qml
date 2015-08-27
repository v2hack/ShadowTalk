/*
 *  文件: picture.qml
 *  功能: 登陆窗口
 *  作者: 南野
 *  时间: 2015年7月13日
 */

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2

Rectangle {
    id: pictureWindowRectangle;

    width: 1200
    height: 700

    color: "black"
    opacity: 0.85
    z: 1000
    radius: 0.7
    border.color: "white"

    /* 主窗口鼠标拖拽 */
    MouseArea {
        id: dragPicture
        anchors.fill: parent
        property point clickPos: "10,10"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y);
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y);
            pictureWindow.setX(pictureWindow.x + delta.x);
            pictureWindow.setY(pictureWindow.y + delta.y);
        }
    }

    states: [
        State {
            name: "hide"
            PropertyChanges {
                target: pictureWindowRectangle
                opacity: 0
                width : 0
                height : 0
            }
        },
        State {
            name: "show"
            PropertyChanges {
                target: pictureWindowRectangle
                opacity: 0.8
                width : 800
                height : 600
            }
        }
    ]
    transitions: [
        Transition {
            from: "hide"
            to: "show"
            NumberAnimation {
                properties: "opacity";
                easing.type: Easing.Linear;
                duration: 500
            }
        },
        Transition {
            from: "show"
            to: "hide"
            NumberAnimation {
                properties: "opacity";
                easing.type: Easing.Linear;
                duration: 500
            }
        }
    ]

    Image {
        id: pictureClose;
        anchors {
            top:parent.top
            topMargin: 5
            right: parent.right
            rightMargin: 5
        }
        height: 40
        width: 40
        source: "qrc:/img/brower/st_pic_close.png";

        MouseArea {
            anchors.fill: parent
            onClicked: {
                pictureWindow.close()
            }
        }
    }

    Image {
        id: pictureLast;
        anchors {
            left: parent.left
            leftMargin: 5
            verticalCenter: parent.verticalCenter
        }
        height: 45
        width: 40
        source: "qrc:/img/brower/st_pic_last.png";

    }

    Image {
        id: pictureNext;
        anchors {
            right: parent.right
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
        height: 45
        width: 40
        source: "qrc:/img/brower/st_pic_next.png";
    }

    Image {
        id: pictureRoll;
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: -40
            bottom: parent.bottom
            bottomMargin: 5
        }
        height: 45
        width: 45
        source: "qrc:/img/brower/st_pic_roll.png";
    }
    Image {
        id: pictureSave;
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: 40
            bottom: parent.bottom
            bottomMargin: 5
        }
        height: 45
        width: 45
        source: "qrc:/img/brower/st_pic_save.png";
    }

    Image {
        id: pictureImage;
        objectName: "qmlNormalImage"
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        function setPicture(picPath, height, width) {
            pictureImage.source = picPath;
            pictureImage.height = height;
            pictureImage.width  = width;
        }
    }
}
