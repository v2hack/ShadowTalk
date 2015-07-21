/*
 *  文件: FriendList.qml
 *  功能: 聊天内容显示
 *  作者: 南野
 *  时间: 2015年7月20日
 */
import QtQuick 2.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "functions.js" as PinYin
import "common.js" as JsCommon

Rectangle {
    id: friendList

    signal sig_add_friend
    signal sig_clear_friend
    color: "transparent"

    function addFriend(name) {
        friendListModel.append({name: name})
    }

    function clearFriend() {
        friendListModel.clear()
    }



    ListView {
        id: friendListView
        anchors.fill: parent;
        delegate: friendListDelegate
        model: friendListModel.createObject(friendListView)

        highlight: highlight
        highlightFollowsCurrentItem: false
        focus: true
        move: Transition {
            NumberAnimation { properties: "x, y"; duration: 1000 }
        }
    }

    Component {
        id: friendListModel
        ListModel {
            //            dynamicRoles: true;
            ListElement {
                name: "南野";
            }
            ListElement {
                name: "hello";
            }
            ListElement {
                name: "123";
            }
            ListElement {
                name: "nanye";
            }
        }
    }

    Component {
        id: friendListDelegate
        Item {
            height:50;
            width:200

            Rectangle {
                id: cellRect
                anchors.fill: parent
                color: "transparent"


                /* 好友item */
                Rectangle {
                    id: friendItem
                    width: 300
                    height: 40
                    color: "transparent"


                    /* 好友头像 */
                    Rectangle {
                        id: friendItemIcon
                        width: 36
                        height: 36
                        radius: width / 2
                        color: JsCommon.getColor(name);
                    }

                    /* 好友名字 */
                    Text {
                        id: friendItemName

                        anchors {
                            left: friendItemIcon.right
                            leftMargin: 4
                        }
                        color: "red"
                        font.pixelSize: 20
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    MouseArea {
                        id: firneItemArea
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onClicked: {
                            // TODO
                        }
                        onEntered: {
                            cellRect.color = "blue";
                        }
                        onExited: {
                            cellRect.color = "transparent";
                        }
                    }
                }

            }
        }
    }
}

