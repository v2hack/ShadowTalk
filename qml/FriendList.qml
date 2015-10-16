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
import st.info.SelectGroup 1.0


Rectangle {
    id: friendList
    anchors.top: parent.top
    color: "transparent"

    /* 网络状态和st_message.h中保持一致 */
    property int fiendOnline  : 1
    property int friendOutline: 2

    property int colorTransparent  : 0

    Component {
        id: sectionHeading
        Rectangle {
            width: 292
            height: 24
            color: "#343434"

            Text {
                text: section
                font.bold: true
                font.pixelSize: 15
                color: "#adadad"

                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 21
                }
            }

        }
    }

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
        id: friendListView
        objectName: "FriendListModel"
        anchors.fill: parent;
        delegate: friendListDelegate
        model: friendListModel.createObject(friendListView)

        highlight: highlight
        highlightFollowsCurrentItem: true
        currentIndex: 4

        section.property: "shortName"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        /* 好友出现的动态效果 */
        add: Transition {
            NumberAnimation {
                property: "opacity";
                from: 0;
                to: 1.0;
                duration: 10
            }
            NumberAnimation {
                property: "scale";
                from: 0;
                to: 1.0;
                duration: 10
            }
        }
        displaced: Transition {
            NumberAnimation {
                properties: "x,y";
                duration: 10;
                easing.type: Easing.OutBounce
            }
        }

        function firstLetter(friendName) {
            var letter = JsCommon.getFirstLetter(friendName);
            if (letter === undefined) {
                letter = "#"
            }
            return letter;
        }

        /* 添加好友 */
        function addFriend(data) {
            data.shortName = JsCommon.getFirstLetter(data.friendName);
            if (data.shortName === undefined) {
                data.shortName = "#"
            }
            model.append(data)
        }

        function addGroup(data) {
            model.append(data)
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
            model.setProperty(index, "messageTime", time);
            model.setProperty(index, "netState", state);
        }
        /* 用于设置被选中的item的背景颜色 */
        function modifyBackColor(index, colorFlag) {
            console.log("[qml] : backGroundColor : index " + index + " color " + colorFlag);
            model.setProperty(index, "backGroundColor", colorFlag);
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

        Rectangle {
            id: deleRect
            width:parent.width
            height:44;

            color: {
                if (backGroundColor == 0) {
                    return "transparent";
                } else if (backGroundColor == 1) {
                    return "#515050";
                }
            }

            Rectangle {
                id: cellRect
                anchors.fill: parent
                color: "transparent"
                width:parent.width
                height:parent.height

                //字体先注释，编译太慢
                FontLoader {
                    id: chineseFont
                    source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                }

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
                    color: "white"
                    font.pixelSize: 15
                    font.letterSpacing: 1
                    text: friendName
                    font.bold: true
                    font.family: chineseFont.name;
                }

                /* 网络状态 */
                Rectangle {
                    id: friendNetState
                    visible: false
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
                        leftMargin: -6;
                        verticalCenter: parent.verticalCenter
                        verticalCenterOffset: 10
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
                        if (shortName === "Group") {
                            console.log("[qml] : select group item - " + friendIndex);
                            selectGroup.changeMessageListForFlist(friendIndex, friendName);
                        } else {
                            console.log("[qml] : select friend item - " + friendIndex);
                            selectFriend.changeMessageListForFlist(friendIndex, friendName);
                        }
                    }
                    onEntered: {
                        friendListScrollbar.visible = true;
                        friendListView.currentIndex = listViewIndex;
                    }
                    onExited: {
                        friendListScrollbar.visible = false;
                        friendListView.currentIndex = -1;
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
            y: friendListView.visibleArea.yPosition * friendListScrollbar.height
            width: 4
            height: friendListView.visibleArea.heightRatio * friendListScrollbar.height;
            color: "#959595"
            radius: 100
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

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

