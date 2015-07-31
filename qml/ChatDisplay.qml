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
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }
    }

    Component {
        id: messageModel
        ListModel {
            //  dynamicRoles: true;
            ListElement {
                uid: 100;
                name: "我";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "一个是TextView的contentWidth的调整fixWidth()";
            }
            ListElement {
                uid: 101;
                name: "张丹";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 1; /* 0: 收到的， 1: 发出的 */
                user_message: "如果你创建一个新的QTextEdit并且想允许用户编辑多信息文本,请调用setTextFormat(Qt::RichText)来确保文本被看做多信息文本。(多信息文本使用HTML标记来设置文本格式属..";
            }
            ListElement {
                uid: 101;
                name: "张丹";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "自己绘制。上所说的估计是Qt 4的东西了。因为Qt Declarative模块就继承自Qt Graphics View。文本展开和行号我觉得可能用tableView会好一些。但没试过，也只是猜测。";
            }
            ListElement {
                uid: 100;
                name: "南野";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 1; /* 0: 收到的， 1: 发出的 */
                user_message: "hellsdfsdfsdfsdrfo world to nanye";
            }
            ListElement {
                uid: 100;
                name: "南野";
                type: 1;  /* 文字:1 图片:2 语音:3 */
                direct: 0; /* 0: 收到的， 1: 发出的 */
                user_message: "hello slkdfgjlkdsfjglfkjglfkds;gjsdgfljglfkds;gjsdgfljglfkds;gjsdgfljglfkds;gjsdgfljglfkds;gjsdgfljglfkds;gjsdgflds;gjsdgflksdgjlfksd;gfjlksdfjglkfsd;jglk;fsdjgflkfdsjglkfdworld to nanye";
            }
        }
    }

    PointSizeToPixelSize {
        id: getPixelSize;
    }

    Component {
        id: messageDelegate

        Item {
            id: messageDelegateItem

            function getItemHeight() {
                var height =  JsCommon.getMessageFrameHeight(
                            getPixelSize.height(10),
                            getPixelSize.width(10 , user_message), 250);

                var row_num = height/17;
                return (row_num * 17) * 1.1 + 40;
            }

            height: getItemHeight();
            width: parent.width;

            /* C++ 计算像素的类 */
            PointSizeToPixelSize {
                id: getPixelSize;
            }

            Rectangle {
                id: messageItem;
                width: 68
                height: messageDelegateItem.height
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
                        top: parent.top
                        topMargin: 5
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
                            topMargin: 10
                            left: direct === 0 ? firendItemImage.right : undefined
                            leftMargin: direct === 0 ? -10 : undefined
                            right: direct == 1 ? firendItemImage.left : undefined
                            rightMargin: direct === 1 ? -16 : undefined
                        }
                        opacity: 0.6
                        source: "qrc:/img/head/st_message_point.png";
                        fillMode: Image.PreserveAspectFit
                        mirror: direct === 0 ? false : true
                    }

                    /* 消息内容 */
                    Rectangle {
                        id: friendMessageContent
                        radius: 10
                        color: "transparent"

                        function getMessageHeight() {
                            var height =  JsCommon.getMessageFrameHeight(
                                        getPixelSize.height(10),
                                        getPixelSize.width(10 , user_message), 250);
//                            console.log("height - " + height);
                            return height * 1.2
                        }

                        function getMessageWidth() {
                            var width = JsCommon.getMessageFrameWidth(
                                        getPixelSize.width(10, user_message)) + 20;
//                            console.log("width - " + width);
                            return width;
                        }

                        height: getMessageHeight();
                        width: getMessageWidth();

                        anchors {
                            top: parent.top
                            topMargin: 20
                            left: direct === 0 ? friendMessagePointImage.right : undefined
                            leftMargin:  direct === 0 ? 3 : undefined
                            right: direct === 1 ? friendMessagePointImage.left : undefined
                            rightMargin: direct === 1 ? 3 :undefined
                        }

                        /* 透明颜色背景 */
                        Rectangle {
                            id: freindMessageContenColor;
                            color: JsCommon.getColor(name);
                            opacity: 0.4
                            radius: 10
                            width: friendMessageContent.width
                            height: friendMessageContent.height;
                            anchors.fill: friendMessageContent
                        }

                        Text {
                            id: friendMessageText
                            width: parent.width
                            anchors {
                                fill: friendMessageContent
                                left:parent.left
                                leftMargin: 10
                            }
                            text: user_message;
                            wrapMode: Text.WrapAnywhere
                            color: "black"
                            font.pointSize: 10
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}

