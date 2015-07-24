/*
 *  文件: FriendList.qml
 *  功能: 好友通讯录
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
    anchors.top: parent.top

    signal sig_add_friend
    signal sig_clear_friend
    color: "transparent"

    function addFriend(name) {
        friendListModel.append({name: name})
    }

    function clearFriend() {
        friendListModel.clear()
    }

    /* 设置在线离线的颜色 */
    function setStateColor(state) {
        if (state === "online") {
            return "#7dc163"
        } else if (state === "outline") {
            return "##a1a1a1";
        } else {
            return "#21ade5"
        }
    }

    /* ListView */
    ListView {
        id: friendListView
        anchors.fill: parent;
        delegate: friendListDelegate
        model: friendListModel.createObject(friendListView)
    }


    /* Model */
    Component {
        id: friendListModel
        ListModel {
            //             dynamicRoles: true;
            ListElement { name: "南野";  }
            ListElement { name: "卢小明"; }
            ListElement { name: "闫立捷"; }
            ListElement { name: "吴自立"; }
            ListElement { name: "刘榴";  }
            ListElement { name: "陈姝";  }
            ListElement { name: "陈宝辉"; }
            ListElement { name: "沈艳匣"; }
            ListElement { name: "严挺"; }
            ListElement { name: "黄松方"; }
            ListElement { name: "闫立捷"; }
            ListElement { name: "吴自立"; }
            ListElement { name: "刘榴"; }
            ListElement { name: "陈姝"; }
            ListElement { name: "陈宝辉"; }
            ListElement { name: "沈艳匣"; }
            ListElement { name: "南野"; }
            ListElement { name: "卢小明"; }
            ListElement { name: "闫立捷"; }
            ListElement { name: "吴自立"; }
            ListElement { name: "刘榴"; }
            ListElement { name: "陈姝"; }
            ListElement { name: "陈宝辉"; }
            ListElement { name: "沈艳匣"; }
        }
    }

    /* Delegate */
    Component {
        id: friendListDelegate
        Item {
            width:284
            height:55;

            Rectangle {
                id: cellRect
                anchors.fill: parent
                color: "transparent"

                /* 好友item */
                Rectangle {
                    id: friendItem
                    width: 300
                    height: 55
                    color: "transparent"

                    /* 好友头像底色 */
                    Rectangle {
                        id: friendItemIcon
                        width: 34
                        height: 34
                        radius: width / 2
                        color: JsCommon.getColor(name);

                        anchors {
                            left: parent.left
                            leftMargin: 14
                            top: parent.top
                            topMargin: 6
                        }
                    }
                    /* 好友头像球体 */
                    Image {
                        width: 65
                        height: 65

                        anchors {
                            top: parent.top
                            topMargin: 1
                            left: parent.left
                            leftMargin: -7
                        }
                        opacity: 1
                        source: "qrc:/img/head/st_ball_white.png";
                        fillMode: Image.PreserveAspectFit
                    }

                    /* 好友名字 */
                    Text {
                        id: friendItemName
                        anchors {
                            left: friendItemIcon.right
                            leftMargin: 6
                            top: parent.top;
                            topMargin: 15
                        }
                        color: "white"
                        font.pixelSize: 15
                        font.letterSpacing: 1
                        text: name
                        font.bold: true

                        /* 字体先注释，编译太慢
                        FontLoader {
                            id: chineseFont
                            source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                        }
                        font.family: chineseFont.name;
                        */
                    }

                    /* 好友上线时间 */
                    Text {
                        id: friendOnlineTime;
                        anchors {
                            right: friendItem.right;
                            rightMargin: 30;
                            top: parent.top;
                            topMargin: 10
                        }
                        color: "white"
                        font.pixelSize: 13
                        text: JsCommon.getDateTime();
                    }

                    /* 在线状态 */
                    Rectangle {
                        id: friendState;
                        width: 13
                        height: 13
                        radius: width / 2
                        color: setStateColor("online");

                        anchors {
                            right: friendItem.right;
                            rightMargin: 30;
                            top: friendOnlineTime.bottom;
                            topMargin: 8
                        }

                        Rectangle {
                            width: 9
                            height: 9
                            radius: width / 2
                            color: parent.color;
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            border.color: "black"
                            border.width: 2
                        }
                    }

                    /* 鼠标滤过的阴影效果 */
                    MouseArea {
                        id: firneItemArea
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onClicked: {
                            cellRect.color = "white";
                            friendListScrollbar.visible = true;
                            cellRect.opacity = 0.9
                        }
                        onEntered: {
                            cellRect.color = "#353535";
                            friendListScrollbar.visible = true;
                            cellRect.opacity = 0.9
                        }
                        onExited: {
                            cellRect.color = "transparent";
                            friendListScrollbar.visible = false;
                            cellRect.opacity = 1
                        }
                        onWheel: {
                            console.log("1 : " + friendListView.contentY);
                            console.log("2 : " + friendListView.contentHeight);
                            console.log(friendListScrollbar.height);

                            if (wheel.angleDelta.y < 0) {
                                if (friendListView.contentY <= friendListView.contentHeight - friendListScrollbar.height) {
                                    friendListView.contentY += 30;
                                }
                            }

                            if (wheel.angleDelta.y > 0 && friendListView.contentY > 0) {
                                friendListView.contentY -= 30;
                            }
                        }
                    }
                }
            }
        }
    }

    /* 滚动条 */
    Rectangle {
        id: friendListScrollbar
        x: 280
        y: 0
        width: 8
        height: parent.height
        color: "transparent"
        visible: false

        // 按钮
        Rectangle {
            id: button
            x: 0
            y: friendListView.visibleArea.yPosition * friendListScrollbar.height
            width: 6
            height: friendListView.visibleArea.heightRatio * friendListScrollbar.height;
            color: "#959595"
            radius: 100

            // 鼠标区域
            MouseArea {
                id: mouseArea2
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: friendListScrollbar.height - button.height

                // 拖动
                onMouseYChanged: {
                    friendListView.contentY = button.y / friendListScrollbar.height * friendListView.contentHeight
                }
            }
        }
    }
}

