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
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "functions.js" as PinYin
import "common.js" as JsCommon

/* 选择好友，动态改变消息栏内容 */
import st.info.SelectFriend 1.0

Rectangle {
    id: searchList
    anchors.top: parent.top
    color: "transparent"

    /* ListView */
    ListView {
        id: searchListView
        objectName: "SearchListModel"
        anchors.fill: parent;
        delegate: searchListDelegate
        model: searchListModel.createObject(searchListView)

        highlightRangeMode: ListView.ApplyRange
        highlightFollowsCurrentItem: true

        /* 好友出现的动态效果 */
        add: Transition {
            NumberAnimation {
                property: "opacity";
                from: 0;
                to: 1.0;
                duration: 200
            }
            NumberAnimation {
                property: "scale";
                from: 0;
                to: 1.0;
                duration: 200
            }
        }
        displaced: Transition {
            NumberAnimation {
                properties: "x,y";
                duration: 200;
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
    }

    /* Model */
    Component {
        id: searchListModel
        ListModel {
            dynamicRoles: true;
            /*
             * cpp传递过来的属性有 friendName, friendIndex, unReadCount
             */
        }
    }

    /* Delegate */
    Component {
        id: searchListDelegate
        Item {
            width:292
            height:44;

            Rectangle {
                id: cellRect
                anchors.fill: parent
                color: "transparent"
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

                    /* 加载字帖 */
                    FontLoader {
                        id: chineseFont
                        source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                    }
                    font.family: chineseFont.name;
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
                        /* TODO: */

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
                            if (searchListView.contentY <= searchListView.contentHeight -
                                    friendListScrollbar.height) {
                                searchListView.contentY += 30;
                            }
                        }
                        if (wheel.angleDelta.y > 0 && searchListView.contentY > 0) {
                            searchListView.contentY -= 30;
                        }
                    }
                }
            }
        }
    }

    /* 滚动条 */
    Rectangle {
        id: friendListScrollbar
        x: 289
        y: 0
        width: 6
        height: parent.height
        color: "transparent"
        visible: false

        // 按钮
        Rectangle {
            id: button
            x: 0
            y: searchListView.visibleArea.yPosition * friendListScrollbar.height
            width: 6
            height: searchListView.visibleArea.heightRatio * friendListScrollbar.height;
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
                    searchListView.contentY = button.y / friendListScrollbar.height * searchListView.contentHeight
                }
            }
        }
    }
}

