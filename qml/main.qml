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
    width: Math.round(890)
    height: Math.round(640)
    radius: 5;

    Drag.active: true

    /* 主窗口可见 */
    visible: true
    /* 透明度 */
    opacity: 0.97

    /* 绘制阴影 */
    /*
    InnerShadow  {
        id: baseShadow;
        cached: true;
        radius: 16;
        samples: 14;
        horizontalOffset: 0
        verticalOffset: 0
        spread: 0.2
        color: "#111111";
        smooth: true;
        source: baseWindows;
    }
    */

    /* 主窗口鼠标拖拽 */
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "10,10"

        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y);
            //            Qt.msetcursor(baseWindows, "SizeAllCursor");
        }
        onReleased: {
            //            Qt.msetcursor(baseWindows, "ArrowCursor");
        }
        onPositionChanged: {
            /* 鼠标偏移量 */
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y);

            //            /* 如果mainwindow继承自QWidget,用setPos */
            mainwindow.setX(mainwindow.x + delta.x);
            mainwindow.setY(mainwindow.y + delta.y);

        }
    }

    /* 主窗口按钮 */
    MainWindowButton {
        id: mainButton;
        width: firstLayerWindows.width - secondLayerWindows.fix_width - 2
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
        id: firstLayerWindows
        width: Math.round(baseWindows.width)
        height: Math.round(baseWindows.height)
        anchors.centerIn: parent
        radius: 5
        border.color: "#a0a0a4"
        border.width: 0

        Rectangle {
            id: secondLayerWindows
            width: Math.round(firstLayerWindows.width - 2)
            height: Math.round(firstLayerWindows.height - 2)
            smooth: true
            radius: 5
            anchors.left: parent.left;
            anchors.leftMargin: 1
            anchors.top: parent.top;
            anchors.topMargin: 1
            property int fix_width: 295
            color: "#efefef"

            /* 背景 */
            Component {
                id: backGroundComponent;
                Rectangle {
                    id: backGroundRectangle
                    width: Math.round(secondLayerWindows.fix_width - 4);
                    height: Math.round(secondLayerWindows.height - 4);
                    color: "#111111"
                    radius: 5
                }
            }

            /* 搜索组件 */
            Component {
                id: searchComponent;
                Rectangle {
                    id: searchRectangle
                    width: Math.round(200)
                    height: Math.round(20)
                    radius: 5
                    color: "#515050"

                    Image {
                        id: searchButton;
                        height: 16
                        width: 15
                        anchors {
                            top: parent.top;
                            topMargin: 2;
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
                anchors.topMargin: 2
                anchors.left: parent.left;
                anchors.leftMargin: 2;
                sourceComponent: backGroundComponent;
            }

            /* 导入搜索栏 */
            Loader {
                id: searchLoader;
                anchors.top: parent.top;
                anchors.topMargin: 8
                anchors.left: backGroundLoader.left
                anchors.leftMargin: secondLayerWindows.fix_width/2 - 100;
                sourceComponent: searchComponent;
            }

            /* 友好及联系人组件 */
            FriendAndContact {
                id: listLoader;
                height: parent.height - 75;
                anchors.top: searchLoader.bottom;
                anchors.topMargin: 6;
                anchors.left: backGroundLoader.left;
                second_layer_width: secondLayerWindows.fix_width;
                second_layer_height: parent.height;
                window_setting_height: 75;
            }

            /* 主页设置按钮 */
            MainWindowSetting {
                id: bottomSettingLoader;
                anchors.top: listLoader.bottom;
                anchors.topMargin: 1
                anchors.left: backGroundLoader.left
                second_layer_width: secondLayerWindows.fix_width;
                second_layer_height: parent.height;
            }

            /* 文字输入对话框 */
            ChatTextInput {
                id: chatTextInputWindow;
                height: 200;
                width: firstLayerWindows.width - secondLayerWindows.fix_width - 2;

                anchors {
                    left: backGroundLoader.right;
                    bottom: backGroundLoader.bottom;
                }
            }

            /* 聊天内容 */
            ChatDisplay {
                id: chatContent;
                height: firstLayerWindows.height - chatTextInputWindow.height - 45;
                width: firstLayerWindows.width - secondLayerWindows.fix_width - 2;
                anchors {
                    left:backGroundLoader.right;
                    bottom: chatTextInputWindow.top;
                }
            }
        }
    }
}
