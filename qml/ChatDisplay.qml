/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: ChatDisplay.qml
 *  简要描述: 聊天内容显示模块
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
import QtMultimedia 5.0

import "functions.js" as PinYin
import "common.js" as JsCommon

/* 导入文字与像素计算类型 */
import st.font.PointSizeToPixelSize 1.0

Rectangle {
    id: messageRectangle;
    color: "#efefef"


    MediaPlayer {
        id: soundMessage
        objectName: "MessageSound"
        autoLoad: true;
        source: "qrc:/sound/message.wav"

        function playMessageSound() {
            soundMessage.play();
        }
    }

    ListView {
        id: messageView;
        objectName: "MessageListModel"
        anchors.fill: parent;
        delegate: messageDelegate
        model: messageModel.createObject(messageView)

        highlightRangeMode: ListView.ApplyRange

        /* 消息出现的动态效果 */
        add: Transition {
             NumberAnimation {
                 property: "opacity";
                 from: 0;
                 to: 1.0;
                 duration: 400
             }
             NumberAnimation {
                 property: "scale";
                 from: 0;
                 to: 1.0;
                 duration: 400
             }
         }
         displaced: Transition {
             NumberAnimation {
                 properties: "x,y";
                 duration: 400;
                 easing.type: Easing.OutBounce
             }
         }

        /* c++调用: 添加消息
         * 这里item是QVariant类型：包含 index、name、type、dircect、user_messsage成员
         */
        function addMessage(data) {
            model.append(data);
            var height =  JsCommon.getMessageFrameHeight(
                        getPixelSize.height(10),
                        getPixelSize.width(10 , data.user_message), 250);
            console.log(height);
            messageView.contentY += height + (100);
        }
        /* c++调用:清除消息 */
        function clearMessage() {
            model.clear();
        }
        /* c++调用:删除一个消息
         * 这里item是QVariant类型：包含 index、count成员
         */
        function removeMessage(item) {
            model.remove(parseInt(item.index),  parseInt(item.count));
        }
    }

    Component {
        id: messageModel
        ListModel {
            dynamicRoles: true;
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
                return (row_num * 17) + 10 + 40;
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
                            return height + 10
                        }

                        function getMessageWidth() {
                            var width = JsCommon.getMessageFrameWidth(
                                        getPixelSize.width(10, user_message)) + 20;
                            return width + 10;
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

