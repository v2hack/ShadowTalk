/*
 *  文件: FriendAndContact.qml
 *  功能: 好友及通讯录列表
 *  作者: 南野
 *  时间: 2015年7月15日
 */
import QtQuick 2.4

Rectangle {
    id:friendAndContact
    property int second_layer_width: 0;    // 外部第二层宽度
    property int second_layer_height: 0;   // 外部第二层高度
    property int window_setting_height: 0; // 主页设置框高度

    Flipable {
        id: flipable

        property bool flipped: false;
        width: friendAndContact.second_layer_width - 4;
        height: 30

        function getMiddleImage() {
            if (flipped === false) {
                return "qrc:/img/choice/st_chat_list.png";
            } else {
                return "qrc:/img/choice/st_contact_list.png"
            }
        }

        Rectangle {
            id: titleFilpable
            width: friendAndContact.second_layer_width - 4;
            height: 30;
            color: "#33ccbf";

            Image {
                id: leftButton;
                width: 25
                height: 18
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left;
                    leftMargin: 0;
                }
                source: "qrc:/img/choice/st_choice_button.png";
                fillMode: Image.PreserveAspectFit
                mirror: true
            }

            Image {
                id: middleImage;
                width: 20
                height: 20
                anchors {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                }
                source: "qrc:/img/choice/st_chat_list.png";
            }

            Image {
                id: rightButton;
                width: 25
                height: 18
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right;
                    rightMargin: 0;
                }
                source: "qrc:/img/choice/st_choice_button.png";
                fillMode: Image.PreserveAspectFit
            }
        }

        /* 前页面-好友列表 */
        front: Rectangle {
            id: friendList
            anchors.top: titleFilpable.bottom;
            width: friendAndContact.second_layer_width - 4;
            height: second_layer_height - titleFilpable.height - window_setting_height;

            color: "#2c2c2c"
            opacity: 0.8

            /* 好友列表细节动态 */
            FriendList {
                id: friendListDisplay;
                height: parent.height - 2;
                width: parent - 8
                anchors {
                    top: friendList.top
                    topMargin: 4
                    left:friendList.left
                    leftMargin: 4
                }
            }
        }

        /* 被页面-联系人列表 */
        back: Rectangle {
            id: contactList
            anchors.top: titleFilpable.bottom;
            width: friendAndContact.second_layer_width - 4
            height: second_layer_height - titleFilpable.height - window_setting_height;
            color: "#2c2c2c"
            opacity: 0.8

            // TODO:
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0;
            axis.y: 1;
            axis.z: 0;
            angle: 0;
        }

        states: State {
            name: "front"
            PropertyChanges {
                target: rotation;
                angle: 180;
            }
            when: flipable.flipped
        }

        transitions: Transition {
            NumberAnimation {
                target: rotation;
                property: "angle";
                duration: 200;
            }
        }

        MouseArea {
            anchors.fill: titleFilpable
            onClicked: {
                flipable.flipped = !flipable.flipped;
                middleImage.source = flipable.getMiddleImage();
                if (middleImage.mirror != false) {
                    middleImage.mirror = false
                }
            }
        }
    }
}

