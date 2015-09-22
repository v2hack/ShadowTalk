/*
 *  文件: mainWindowButton.qml
 *  功能: 主要是窗口按钮UI实现
 *  作者: 南野
 *  时间: 2015年7月15日
 */
import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id:mainWindowButton

    /* 当前用户名显示 */
    Rectangle {
        id: displayFirnedName;
        objectName: "DispalyCurrentFriendName"
        height:35
        width: 50
        color: "transparent"

        function setCurrentFriendName(name) {
            currentFriendName.text = name;
        }
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        Text {
            id: currentFriendName;
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: 16
            font.bold: true
            color: "#515050"

            FontLoader {
                id: chineseFont
                source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
            }
            font.family: chineseFont.name;
        }
    }

    /* 添加关闭按钮 */
    Rectangle {
        id: windowCloseButton
        height: 20
        width: 20
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 13
        color: parent.color

        Image {
            id: closeButtonImage;
            height: 11
            width: 11
            source: "qrc:/img/st_button_close_1.png";
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            id: closeButtonArea
            anchors.fill: parent;
            hoverEnabled: true;

            onClicked: {
                mainwindow.close()
            }
            onEntered: {
                closeButtonImage.source = "qrc:/img/st_button_close_2.png"
            }
            onExited: {
                closeButtonImage.source = "qrc:/img/st_button_close_1.png"
            }
        }
    }

    /* 添加最大化按钮 */
    Rectangle {
        id: windowMaxButton
        height: 15
        width: 15
        anchors.right: windowCloseButton.left
        anchors.rightMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 13
        color: parent.color

        property bool window_max_flag: false;

        Image {
            id: maxButtonImage1;
            height: 12
            width: 12
            source: "qrc:/img/st_button_max_1.png";
            fillMode: Image.PreserveAspectFit
            visible: true;
        }

        Image {
            id: maxButtonImage2;
            height: 12
            width: 12
            source: "qrc:/img/st_button_normal_1.png";
            fillMode: Image.PreserveAspectFit
            visible: false;
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true;
            onClicked: {
                if (parent.window_max_flag == false) {
                    mainwindow.showMaximized();
                    maxButtonImage1.visible = false;
                    maxButtonImage2.visible = true;
                    parent.window_max_flag = true;
                } else {
                    mainwindow.showNormal();
                    maxButtonImage1.visible = true;
                    maxButtonImage2.visible = false;
                    parent.window_max_flag = false;
                }
            }
            onEntered: {
                if (parent.window_max_flag == false) {
                    maxButtonImage1.source = "qrc:/img/st_button_max_2.png"
                } else {
                    maxButtonImage2.source = "qrc:/img/st_button_normal_2.png"
                }
            }
            onExited: {
                if (parent.window_max_flag == false) {
                    maxButtonImage1.source = "qrc:/img/st_button_max_1.png"
                } else {
                    maxButtonImage2.source = "qrc:/img/st_button_normal_1.png"
                }
            }
        }
    }

    /* 添加最小化按钮 */
    Rectangle {
        id: windowMinButton
        height: 15
        width: 15
        anchors.right: windowMaxButton.left
        anchors.rightMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 17
        color: parent.color

        Image {
            id: minButtonImage;
            height: 12
            width: 12
            source: "qrc:/img/st_button_min_1.png";
            fillMode: Image.PreserveAspectFit
        }

        MouseArea{
            height: 40
            width: 40
            anchors.centerIn: parent
            anchors.fill: parent
            hoverEnabled: true;

            onClicked: {
                mainwindow.showMinimized();
            }
            onEntered: {
                minButtonImage.source = "qrc:/img/st_button_min_2.png"
            }
            onExited: {
                minButtonImage.source = "qrc:/img/st_button_min_1.png"
            }
        }
    }
}

