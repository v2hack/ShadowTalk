/*
 *  文件: main.qml
 *  功能: 主窗口按钮UI布局
 *  作者: 南野
 *  时间: 2015年7月13日
 */

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

Rectangle {
    id: baseWindows;
    objectName: "RootBaseWindow";

    function setBaseWindowVisible() {
        baseWindows.visible = true;
    }
    function setBaseWindowUnvisible() {
        baseWindows.visible = false;
    }

    width: 890
    height: 640

    Drag.active: true
    border.color: "#2c2c2c"
    border.width: 2

    /* 主窗口可见 */
    visible: true
    /* 透明度 */
    opacity: 0.97

    /* 主窗口鼠标拖拽 */
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "10,10"

        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y);
        }
        onPositionChanged: {
            /* 鼠标偏移量 */
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y);
            mainwindow.setX(mainwindow.x + delta.x);
            mainwindow.setY(mainwindow.y + delta.y);
        }
    }

    /* 主窗口按钮 */
    MainWindowButton {
        id: mainButton;
        width: parent.width - 310
        height: 40;
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.top: parent.top
        anchors.topMargin: 0
        color: "#efefef"
        opacity: 1
        z:100
    }

    /* 主窗口 */
    Rectangle {
        id: secondLayerWindows
        width: baseWindows.width
        height: baseWindows.height
        smooth: true
        anchors.left: parent.left;
        anchors.top: parent.top;
        property int fix_width: 296
        color: "#efefef"

        /* 背景 */
        Component {
            id: backGroundComponent;
            Rectangle {
                id: backGroundRectangle
                width: secondLayerWindows.fix_width;
                height: secondLayerWindows.height;
                color: "#2c2c2c"
            }
        }

        /* 软件图标 */
        Image {
            id: softwareIcon
            height: 19
            width: 19
            anchors {
                top: parent.top
                topMargin: 3
                left: parent.left;
                leftMargin: 3;
            }
            source: "qrc:/img/st_icon.png";
            fillMode: Image.PreserveAspectFit
        }

        /* 搜索组件 */
        Component {
            id: searchComponent;
            Rectangle {
                id: searchRectangle
                width: Math.round(250)
                height: Math.round(26)
                radius: 3
                color: "#515050"

                Image {
                    id: searchButton;
                    height: 16
                    width: 26
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left;
                        leftMargin: 5;
                    }
                    source: "qrc:/img/st_button_search.png";
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        /* 导入背景 */
        Loader {
            id: backGroundLoader;
            anchors.top: parent.top;
            anchors.left: parent.left;
            sourceComponent: backGroundComponent;
        }

        /* 搜索栏 */
        Loader {
            id: searchLoader;
            anchors {
                top: parent.top;
                topMargin: 50
                left: parent.left
                leftMargin: (secondLayerWindows.fix_width - 250)/2
            }
            sourceComponent: searchComponent;
        }

        /* 友好及联系人组件 */
//        FriendAndContact {
//            id: listLoader;
//            height: parent.height - 75;
//            anchors.top: searchLoader.bottom;
//            anchors.topMargin: 6;
//            anchors.left: backGroundLoader.left;
//            second_layer_width: secondLayerWindows.fix_width;
//            second_layer_height: parent.height;
//            window_setting_height: 75;
//        }

        /* 主页设置按钮 */
//        MainWindowSetting {
//            id: bottomSettingLoader;
//            anchors.top: listLoader.bottom;
//            anchors.topMargin: 1
//            anchors.left: backGroundLoader.left
//            second_layer_width: secondLayerWindows.fix_width;
//            second_layer_height: parent.height;
//        }

        /* 文字输入对话框 */
        ChatTextInput {
            id: chatTextInputWindow;
            height: 200;
            width: baseWindows.width - secondLayerWindows.fix_width - 2;

            anchors {
                left: backGroundLoader.right;
                bottom: backGroundLoader.bottom;
            }
        }

        /* 聊天内容 */
        ChatDisplay {
            id: chatContent;
            height: baseWindows.height - chatTextInputWindow.height - 45;
            width: baseWindows.width - secondLayerWindows.fix_width - 2;
            anchors {
                left:backGroundLoader.right;
                bottom: chatTextInputWindow.top;
            }
        }
    }
}
