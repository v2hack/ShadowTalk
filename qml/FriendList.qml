/*
 *  文件: FriendList.qml
 *  功能: 好友通讯录
 *  作者: 南野
 *  时间: 2015年7月20日
 */
import QtQuick 2.4
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "functions.js" as PinYin
import "common.js" as JsCommon

/* 选择好友，动态改变消息栏内容 */
import st.info.SelectFriend 1.0


Rectangle {
    id: friendList
    anchors.top: parent.top
    color: "transparent"

    /* ListView */
    ListView {
        id: friendListView
        objectName: "FriendListModel"
        anchors.fill: parent;
        delegate: friendListDelegate
        model: friendListModel.createObject(friendListView)

         highlightRangeMode: ListView.ApplyRange
         highlightFollowsCurrentItem: true
        /* 好友出现的动态效果 */
        add: Transition {
             NumberAnimation {
                 property: "opacity";
                 from: 0;
                 to: 1.0;
                 duration: 1000
             }
             NumberAnimation {
                 property: "scale";
                 from: 0;
                 to: 1.0;
                 duration: 1000
             }
         }
         displaced: Transition {
             NumberAnimation {
                 properties: "x,y";
                 duration: 1000;
                 easing.type: Easing.OutBounce
             }
         }

        /* 添加好友 */
        function addFriend(data) {
            model.append(data)
        }

        /* 清理所有好友 */
        function clearFriend() {
            model.clear()
        }

        /* 修改好友名字 */
        function modifyFriendName() {

        }

        /* 修改未读消息数量 */
        function modifyUnreadCount(index, count) {
            model.setProperty(index, "unReadCount", count);
        }
    }


    /* Model */
    Component {
        id: friendListModel
        ListModel {
            dynamicRoles: true;
            /*
             * cpp传递过来的属性有 friendName, friendIndex, unReadCount
             */
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
                        color: JsCommon.getColor(friendName);

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
                        text: friendName
                        font.bold: true

                        //字体先注释，编译太慢
                        FontLoader {
                            id: chineseFont
                            source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                        }
                        font.family: chineseFont.name;
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
                        font.family: chineseFont.name;
                    }

                    /* 未读消息数量 */
                    Rectangle {
                        id: unReadCountRectangle;

                        width : 18
                        height: 18
                        radius: width / 2
                        color : "red";
                        visible: unReadCount == 0 ? false : true

                        anchors {
                            right: friendItem.right;
                            rightMargin: 30;
                            top: friendOnlineTime.bottom;
                            topMargin: 5
                        }

                        Text {
                            id: unReadText
                            anchors {
                                horizontalCenter:parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                            color: "white"
                            font.pixelSize: 12
                            font.bold: true
                            text: unReadCount > 99 ? "99+" : unReadCount
                            font.family: chineseFont.name;
                        }
                    }

                    /* cpp层类对象 */
                    SelectFriend {
                        id: selectFriend
                    }

                    /* 鼠标滤过的阴影效果 */
                    MouseArea {
                        id: firneItemArea
                        anchors.fill: parent;
                        hoverEnabled: true;

                        onClicked: {
                            cellRect.color = "#444555";
                            friendListScrollbar.visible = true;
                            cellRect.opacity = 0.9;
                            /* 选中好友，消息栏同步更新 */
                            selectFriend.changeMessageList(friendIndex, friendName);
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
                            if (wheel.angleDelta.y < 0) {
                                if (friendListView.contentY <= friendListView.contentHeight -
                                        friendListScrollbar.height) {
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

