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

    /* ListView */
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

    /* Model */
    Component {
        id: friendListModel
        ListModel {
            //            dynamicRoles: true;
            ListElement {
                name: "南野";
            }
            ListElement {
                name: "卢小明";
            }
            ListElement {
                name: "闫立捷";
            }
            ListElement {
                name: "吴自立";
            }
            ListElement {
                name: "刘榴";
            }
            ListElement {
                name: "陈姝";
            }
            ListElement {
                name: "陈宝辉";
            }
            ListElement {
                name: "沈艳匣";
            }
        }
    }

    /* Delegate */
    Component {
        id: friendListDelegate
        Item {
            height:50;
            width:284

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
                    anchors.verticalCenter: parent.verticalCenter

                    /* 好友头像 */
                    Rectangle {
                        id: friendItemIcon
                        width: 31
                        height: 31
                        radius: width / 2
                        color: JsCommon.getColor(name);

                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 10
                        }
                    }

                    /* 好友名字 */
                    Text {
                        id: friendItemName

                        anchors {
                            left: friendItemIcon.right
                            leftMargin: 8
                            verticalCenter: parent.verticalCenter
                        }
                        color: "white"
                        font.pixelSize: 15
                        text: name
                        style: Text.Raised;

                    }

                    MouseArea {
                        id: firneItemArea
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onClicked: {
                            // TODO
                        }
                        onEntered: {
                            cellRect.color = "#353535";
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

