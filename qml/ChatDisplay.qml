/*
 *  文件: ChatDisplay.qml
 *  功能: 聊天内容显示模块
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
    id: messageRectangle;
    color: "#efefef"

    function addMessage(uid, name, type) {
        messageModel.append({
                                uid: uid,
                                name: name,
                                type: type,
                            })
    }
    function cleanMessage() {
        messageModel.clear()
    }


    ListView {
        id: messageView;
        anchors.fill: parent;
        delegate: messageDelegate
        model: messageModel.createObject(messageView)

        highlight: highlight
        highlightFollowsCurrentItem: false
        focus: true
        move: Transition {
            NumberAnimation { properties: "x, y"; duration: 1000 }
        }
    }

    Component {
        id: messageModel
        ListModel {
            //  dynamicRoles: true;
            ListElement {
                uid: 100;
                name: "南野";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                driect: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "hello world";
            }

        }
    }


    Component {
        id: messageDelegate

        Item {
            height:100

            Rectangle {
                id: messageItem;
                anchors.fill: parent
                color: "transparent"

                /* 好友头像 */
                Rectangle {
                    id: friendItemIcon
                    width: 36
                    height: 36
                    radius: width / 2
                    color: JsCommon.getColor(name);

                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 14
                    }
                    /* 好友头像球体 */
                    Image {
                        id: firendItemImage
                        width: 68
                        height: 68

                        anchors {
                            top: parent.top
                            topMargin: -5
                            left: parent.left
                            leftMargin: -21
                        }
                        opacity: 1
                        source: "qrc:/img/head/st_ball_white.png";
                        fillMode: Image.PreserveAspectFit
                    }
                    /* 好友名字 */
                    Text {
                        id: friendItemName

                        anchors {
                            fill: parent
                            top: parent.top
                            topMargin: 12
                            left:parent.left
                            leftMargin: 5
                        }

                        color: "#cecece"
                        font.pixelSize: 12
                        text: name
                        font.bold: true
                        font.family: "Cronyx"
                        font.letterSpacing: 2
                        style: Text.Raised


                        /* 字体先注释，编译太慢
                        FontLoader {
                            id: chineseFont
                            source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                        }
                        font.family: chineseFont.name;
                        */
                    }

                    /* 对话框小箭头 */
                    Image {
                        id: friendMessagePointImage
                        width: 30
                        height: 30

                        anchors {
                            top: parent.top
                            topMargin: 8
                            left: firendItemImage.right
                            leftMargin: -5
                        }
                        opacity: 1
                        source: "qrc:/img/head/st_message_point.png";
                        fillMode: Image.PreserveAspectFit
                    }

                    Rectangle {
                        id: friendMessageContent
                        anchors {
                            top: parent.top
                            topMargin: 8
                            left: friendMessagePointImage.right
                            leftMargin: 0
                        }

                        width: JsCommon.getMessageFrameWidth(user_message, messageRectangle.width);
                        height: JsCommon.getMessageFrameHeight(user_message, friendMessageContent.width) + 4;
                        color: "transparent"

                        BorderImage {
                            id: friendMessageFrameImage
//                            width: parent.width - 5
//                            height: parent.height - 5
                            width: 300
                            height:300
                            source: "qrc:/img/head/st_message_frame.png";
//                            fillMode: Image.PreserveAspectFit

                        }
                    }
                }
            }
        }
    }
}

