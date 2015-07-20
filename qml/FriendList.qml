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

Rectangle {
    id: friendList

    signal sig_add_friend
    signal sig_clear_friend

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
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }
    }

    Component {
        id: friendListModel
        ListModel {
//            dynamicRoles: true;
            ListElement {
                name: "成都";
            }
            ListElement {
                name: "成都";
            }
        }
    }

    Component {
        id: friendListDelegate
        Item {
            height:20;
            width:30
            Rectangle {
                id: cellRect
                anchors.fill: parent

                Text {
                    color: "red"
                    font.pixelSize: 20
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}

