/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: ChatList.qml
 *  简要描述: 聊天好友临时列表
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.2

import "functions.js" as PinYin
import "common.js" as JsCommon

/* 选择好友，动态改变消息栏内容 */
import st.info.SelectFriend 1.0
import st.info.SelectGroup 1.0

Rectangle {
    id: chatList
    anchors.top: parent.top
    color: "transparent"

    /* 网络状态和st_message.h中保持一致 */
    property int fiendOnline  : 1
    property int friendOutline: 2

    Component {
        id: highlight
        Rectangle {
            width: 292
            height:44;
            color: "#3a3a3a";
            radius: 5
        }
    }

    /* ListView */
    ListView {
        id: chatListView
        objectName: "ChatListModel"
        anchors.fill: parent;
        delegate: chatListDelegate
        model: chatListModel.createObject(chatListView)

        highlight: highlight
        highlightFollowsCurrentItem: true

        /* 好友出现的动态效果 */
        add: Transition {
            NumberAnimation {
                property: "opacity";
                from: 0;
                to: 1.0;
                duration: 20
            }
            NumberAnimation {
                property: "scale";
                from: 0;
                to: 1.0;
                duration: 20
            }
        }
        displaced: Transition {
            NumberAnimation {
                properties: "x,y";
                duration: 20;
                easing.type: Easing.OutBounce
            }
        }

        /* 添加好友 */
        function addFriend(data) {
            model.append(data);
        }

        /* 顶部插入 */
        function insertFriend(data) {
            model.insert(0, data);
        }

        function removeFriend(chatIndex) {
            model.remove(chatIndex);
        }

        /* 清理所有好友 */
        function clearFriend() {
            model.clear()
        }

        /* 修改未读消息数量 */
        function modifyUnreadCount(index, count) {
            model.setProperty(index, "unReadCount", count);
        }

        /* 修改还有最后一条信息的时间 */
        function modifyFriendTime(index, time, state) {
            model.setProperty(index, "netState", state);
        }
        /* 用于设置被选中的item的背景颜色 */
        function modifyBackColor(index, colorFlag) {
            model.setProperty(index, "backGroundColor", colorFlag);
        }

        function updateListIndex(index, newIndex) {
            model.setProperty(index, "listViewIndex", newIndex);
        }
    }


    /* Model */
    Component {
        id: chatListModel
        ListModel {
            dynamicRoles: true;
            /*
             * cpp传递过来的属性有 friendName, friendIndex, unReadCount
             */
        }
    }

    /* Delegate */
    Component {
        id: chatListDelegate
        Item {
            width:292
            height:44;

            /* 加载字帖 */
            FontLoader {
                id: chineseFont
                source: "qrc:/res/fonts/fangzheng_gbk.ttf"
            }

            Rectangle {
                id: cellRect
                anchors.fill: parent
                color: {
                    if (backGroundColor == 0) {
                        return "transparent";
                    } else if (backGroundColor == 1) {
                        return "#515050";
                    }
                }
                width: parent.width
                height: parent.height

                /* 好友头像底色 */
                Rectangle {
                    id: friendItemIcon
                    width: 34
                    height: 34
                    radius: width / 2
                    color: {
                        var ret = JsCommon.getColor(friendName);
                        if (ret === undefined) {
                            return "#7c509d"
                        }
                        return ret;
                    }

                    anchors {
                        left: parent.left
                        leftMargin: 16
                        verticalCenter: parent.verticalCenter
                    }
                    Text {
                        id: shortNameText
                        anchors {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                        }
                        color: "white"
                        font.pixelSize: 12
                        font.letterSpacing: 1
                        font.bold: true
                        text: JsCommon.getShortName(friendName);
                        font.family: chineseFont.name;
                    }
                }

                /* 好友名字 */
                Text {
                    id: friendItemName
                    anchors {
                        left: friendItemIcon.right
                        leftMargin: 12
                        verticalCenter: parent.verticalCenter
                    }
                    color: "black"
                    font.pixelSize: 15
                    font.letterSpacing: 1
                    text: friendName
                    font.bold: true
                    font.family: chineseFont.name;
                }

                /* 好友网络状态 */
                Rectangle {
                    id: friendNetState
                    width: 13
                    height: 13
                    radius: width / 2
                    color: netState == fiendOnline ? "green" : "white"

                    anchors {
                        right: cellRect.right
                        rightMargin: 30
                        verticalCenter: parent.verticalCenter
                    }

                    Rectangle {
                        border.color: "#282828"
                        border.width: 2

                        color: netState == fiendOnline ? "green" : "white"
                        width: 11
                        height: 11
                        radius: width / 2
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            verticalCenter: parent.verticalCenter
                        }
                    }
                }

                /* 未读消息数量 */
                Rectangle {
                    id: unReadCountRectangle;

                    width : 16
                    height: 16
                    radius: width / 2
                    color : "red";
                    visible: unReadCount == 0 ? false : true

                    anchors {
                        left: friendItemIcon.right;
                        leftMargin: -8;
                        verticalCenter: parent.verticalCenter
                        verticalCenterOffset: -10
                    }

                    Text {
                        id: unReadText
                        anchors {
                            horizontalCenter:parent.horizontalCenter
                            verticalCenter: parent.verticalCenter
                        }
                        color: "white"
                        font.pixelSize: 10
                        font.bold: true
                        text: unReadCount > 99 ? "99+" : unReadCount
                        font.family: chineseFont.name;
                    }
                }

                /* cpp层类对象 */
                SelectFriend {
                    id: selectFriend
                }
                SelectGroup {
                    id: selectGroup
                }

                /* 鼠标滤过的阴影效果 */
                MouseArea {
                    id: firneItemArea
                    anchors.fill: parent;
                    hoverEnabled: true;

                    onClicked: {
                        friendListScrollbar.visible = true;
                        /* 选中好友，消息栏同步更新 */
                        baseWindows.showContent(0);
                        selectFriend.changeMessageListForClist(friendIndex, friendName);

                        if (shortName === "Group") {
                            console.log("select group item - " + friendIndex + " - " + friendName + " - " + shortName);
                            selectGroup.changeMessageListForClist(friendIndex, friendName);
                        } else {
                            console.log("select friend item - " + friendIndex + " - " + friendName + " - " + shortName);
                            selectFriend.changeMessageListForClist(friendIndex, friendName);
                        }
                    }
                    onEntered: {
                        friendListScrollbar.visible = true;
                        chatListView.currentIndex = listViewIndex;
                    }
                    onExited: {
                        friendListScrollbar.visible = false;
                        chatListView.currentIndex = -1;
                    }
                    onWheel: {
                        if (wheel.angleDelta.y < 0) {
                            if (chatListView.contentY <= chatListView.contentHeight -
                                    friendListScrollbar.height) {
                                chatListView.contentY += 30;
                            }
                        }
                        if (wheel.angleDelta.y > 0 && chatListView.contentY > 0) {
                            chatListView.contentY -= 30;
                        }
                    }
                }
            }
        }
    }

    /* 滚动条 */
    Rectangle {
        id: friendListScrollbar
        x: 291
        y: 0
        width: 4
        height: parent.height
        color: "transparent"
        visible: false

        // 按钮
        Rectangle {
            id: button
            x: 0
            y: chatListView.visibleArea.yPosition * friendListScrollbar.height
            width: 4
            height: chatListView.visibleArea.heightRatio * friendListScrollbar.height;
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
                    chatListView.contentY = button.y / friendListScrollbar.height * chatListView.contentHeight
                }
            }
        }
    }
}

