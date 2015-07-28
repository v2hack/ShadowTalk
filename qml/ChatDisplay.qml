/*
 *  文件: ChatDisplay.qml
 *  功能: 聊天内容显示模块
 *  作者: 南野
 *  时间: 2015年7月20日
 */
import QtQuick 2.4
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "functions.js" as PinYin
import "common.js" as JsCommon

/* 导入文字与像素计算类型 */
import st.font.PointSizeToPixelSize 1.0

Rectangle {
    id: messageRectangle;
    color: "#efefef"

    function addMessage(uid, name, type) {
        messageModel.append({uid: uid, name: name, type: type,});
    }

    function cleanMessage() {
        messageModel.clear();
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
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "hello world to nanye";
            }
            ListElement {
                uid: 101;
                name: "张丹";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 1; /* 0: 收到的， 1: 发出的 */
                user_message: "hello sdfgkhjdslfkghjksdlxjgfhlksdjhglkjsdhgjfsdgworld to nanye";
            }
            ListElement {
                uid: 101;
                name: "张丹";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 1; /* 0: 收到的， 1: 发出的 */
                user_message: "hello worlddsgkhjfdsjhgfsdg to nanye";
            }
            ListElement {
                uid: 100;
                name: "南野";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "hello world to nanye";
            }
            ListElement {
                uid: 100;
                name: "南野";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "hello slkdfgjlkdsfjglfkds;gjsdgflksdgjlfksd;gfjlksdfjglkfsd;jglk;fsdjgflkfdsjglkfdworld to nanye";
            }
        }
    }

    Component {
        id: messageDelegate

        Item {
            height:JsCommon.getMessageFrameHeight(user_message, 300) + 10
            width: parent.width

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
                        left:  direct === 0 ? parent.left : undefined
                        leftMargin: direct === 0 ? 14 : undefined
                        right: direct === 1 ? parent.right : undefined
                        rightMargin: direct === 1 ? 14 : undefined
                    }
                    /* 好友头像球体 */
                    Image {
                        id: firendItemImage
                        width: 68
                        height: 68

                        anchors {
                            top: parent.top
                            topMargin: -5
                            left: direct === 0 ? parent.left : undefined
                            leftMargin: direct === 0 ? -21 : undefined
                            right: direct === 1 ? parent.right : undefined
                            rightMargin: direct === 1 ? -11 : undefined
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
                            topMargin: 7
                            left: direct === 0 ? firendItemImage.right : undefined
                            leftMargin: direct === 0 ? -5 : undefined
                            right: direct == 1 ? firendItemImage.right : undefined
                            rightMargin: direct === 1 ? 53 : undefined
                        }
                        opacity: 0.6
                        source: "qrc:/img/head/st_message_point.png";
                        fillMode: Image.PreserveAspectFit
                        mirror: direct === 0 ? false : true
                    }

                    /* 消息内容 */
                    Rectangle {
                        id: friendMessageContent
                        anchors {
                            top: parent.top
                            topMargin: 8
                            left: direct === 0 ?  friendMessagePointImage.right : undefined
                            leftMargin:  direct === 0 ? 1 : undefined
                            right: direct === 1 ? friendMessagePointImage.left : undefined
                            rightMargin: direct === 1 ? 1 :undefined
                        }
                        opacity: 0.3

//                        width: JsCommon.getMessageFrameWidth(user_message, 300);
//                        height: JsCommon.getMessageFrameHeight(user_message, 300);
                        color: "transparent"


                        width: JsCommon.getMessageFrameWidth(getPixelSize.width(10, user_message));
                        height: JsCommon.getMessageFrameHeight(getPixelSize.height(10), getPixelSize.width(10, user_message)) + 10;

                        PointSizeToPixelSize {
                            id: getPixelSize;
                        }

                        BorderImage {
                            id: friendMessageFrameImage

                            border.top: 40;
                            border.bottom: 40;
                            border.left: 40;
                            border.right: 40;
                            smooth: true
                            width: friendMessageContent.width + 60
                            height: friendMessageContent.height + 2
                            source: "qrc:/img/head/st_message_frame.png";
                        }


                        Text {
                            anchors {
                                fill: parent
                                top: parent.top
                                topMargin: 5
                                left:parent.left
                                leftMargin: 5
                            }
                            text: user_message;
                            wrapMode: Text.Wrap
                            color: "black"
                            font.pointSize: 10
                            horizontalAlignment: direct === 0 ? Text.AlignLeft : Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}

