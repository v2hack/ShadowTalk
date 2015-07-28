/*
 *  文件: FriendAndContact.qml
 *  功能: 好友及通讯录列表
 *  作者: 南野
 *  时间: 2015年7月15日
 */
import QtQuick 2.4
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Rectangle {
    id: bottomSettingComponent;
    property int second_layer_width: 0;
    property int second_layer_height: 0;

    Rectangle {
        id: bottomSettingComponentRectangle;
        width: Math.round(second_layer_width - 4);
        height: Math.round(37);
        radius: 5;
        color: "#515050"

        /* 退出按钮 */
        Button {
            id: exitButton;
            text: "";
            width: 20;
            height: 25;
            Image {
                id: exitButtonImage1;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_exit_1.png";
                fillMode: Image.PreserveAspectFit;
                visible: true;
            }

            Image {
                id: exitButtonImage2;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_exit_2.png";
                fillMode: Image.PreserveAspectFit;
                visible: false;
            }

            style: ButtonStyle {
                background: Rectangle {
                    opacity: 0
                }
            }
            anchors.left: parent.left;
            anchors.leftMargin: parent.width/4 - 16;
            anchors.top: parent.top;
            anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;

            MouseArea {
                id: exitButtonArea
                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                    // TODO
                }
                onEntered: {
                    exitButtonImage1.visible = false;
                    exitButtonImage2.visible = true;
                }
                onExited: {
                    exitButtonImage1.visible = true;
                    exitButtonImage2.visible = false;
                }
            }
        }


        /* 声音按钮 */
        Button {
            id: soundButton;
            width: 30;
            height: 25;

            Image {
                id: soundButtonImage1;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_sound_1.png";
                fillMode: Image.PreserveAspectFit;
                visible: true;
            }

            Image {
                id: soundButtonImage2;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_sound_2.png";
                fillMode: Image.PreserveAspectFit;
                visible: false;
            }

            style: ButtonStyle {
                background: Rectangle {
                    opacity: 0
                }
            }
            anchors.left: parent.left;
            anchors.leftMargin: parent.width/2 - 16;
            anchors.top: parent.top;
            anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;

            MouseArea {
                id: soundButtonArea;
                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                    // TODO
                }
                onEntered: {
                    soundButtonImage1.visible = false;
                    soundButtonImage2.visible = true;
                }
                onExited: {
                    soundButtonImage1.visible = true;
                    soundButtonImage2.visible = false;
                }
            }
        }

        /* 锁屏按钮 */
        Button {
            id: lockScreenButton;
            width: 33;
            height: 28;

            style: ButtonStyle {
                background: Rectangle {
                    opacity: 0
                }
            }

            Image {
                id: lockButtonImage1;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_lock_screen_1.png";
                fillMode: Image.PreserveAspectFit;
                visible: true;
            }

            Image {
                id: lockButtonImage2;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_lock_screen_2.png";
                fillMode: Image.PreserveAspectFit;
                visible: false;
            }

            anchors.left: parent.left;
            anchors.leftMargin: parent.width/4*3 - 16;
            anchors.top: parent.top;
            anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;

            MouseArea {
                id: lockButtonArea;
                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                    // TODO
                }
                onEntered: {
                    lockButtonImage1.visible = false;
                    lockButtonImage2.visible = true;
                }
                onExited: {
                    lockButtonImage1.visible = true;
                    lockButtonImage2.visible = false;
                }
            }
        }
    }

}

