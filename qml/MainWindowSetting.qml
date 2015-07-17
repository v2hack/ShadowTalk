/*
 *  文件: FriendAndContact.qml
 *  功能: 好友及通讯录列表
 *  作者: 南野
 *  时间: 2015年7月15日
 */
import QtQuick 2.0
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
                id: exitButtonImage;
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_exit.png";
                fillMode: Image.PreserveAspectFit
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
        }


        /* 声音按钮 */
        Button {
            id: soundButton;
            width: 30;
            height: 25;
            Image {
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_sound.png"
                fillMode: Image.PreserveAspectFit
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
                width: parent.width;
                height: parent.height;
                source: "qrc:/img/st_setting_lock_screen.png"
                fillMode: Image.PreserveAspectFit
            }
            anchors.left: parent.left;
            anchors.leftMargin: parent.width/4*3 - 16;
            anchors.top: parent.top;
            anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;
        }
    }

}

