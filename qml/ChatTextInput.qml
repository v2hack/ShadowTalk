/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: ChatTextInput.qml
 *  简要描述: 聊天输入框
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

import st.info.MessageManager 1.0

Rectangle {
    id: chatTextInput
    z:400

    property int friendIndex: 0

    /* 输入工具栏 */
    Rectangle {
        id: chatTool
        width: parent.width;
        height: 1;
        opacity: 0.3
        color: "#979797"
    }


    /* C++ 发送接口 */
    MessageManager {
        id: cppSendMessage;
    }

    /* 发送消息链接 */
    Connections {
        target: chatMouseArea

        onClicked: {
            /* TODO: 这里要修改为具体发送消息 */
            if (chatTextEdit.text != "") {
                cppSendMessage.sendMessage(friendIndex, chatTextEdit.text);
                /* 清理数据需要恢复光标的位置 */
                chatTextEdit.cursorPosition = 0;
                chatTextEdit.text = "";
            }
        }
    }


    /* 聊天内容发送框 */
    Rectangle {
        id: chatTextEditRectangle;
        width: parent.width;
        height: parent.height - chatTool.height - 35;
        color: "#efefef"

        anchors {
            top: chatTool.bottom;
        }

        /* 输入编辑栏 */
        TextArea {
            id: chatTextEdit;
            anchors.fill: chatTextEditRectangle;
            wrapMode: Text.WrapAnywhere
            selectByMouse: true
            backgroundVisible: false
            frameVisible: false
            font.family: chineseFont.name;

            focus: true
            Keys.onReturnPressed: {
                if (chatTextEdit.text != "") {
                    /* TODO: 这里要修改为具体发送消息 */
                    cppSendMessage.sendMessage(friendIndex, chatTextEdit.text);
                    /* 恢复提示符位置 */
                    chatTextEdit.cursorPosition = 0;
                    /* 清理内容 */
                    chatTextEdit.text = "";
                }
            }
        }
    }

    /* 发送按钮所在的矩形条 */
    Rectangle {
        id: chatTextSendRectangle
        width: parent.width;
        height: 35;
        color: "#efefef"

        anchors {
            top: chatTextEditRectangle.bottom
        }

        /* 发送消息按钮 */
        Rectangle {
            id: chatTextSendButton
            width: 72
            height: 26
            color: "#efefef"
            border.color: "#afafaf"

            anchors {
                right: parent.right
                rightMargin: 10
                top: parent.top
                topMargin: 5
            }

            Text {
                id: chatSendText
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                color: "#4f4f4f"
                font.pixelSize: 12
                font.bold: true
                font.letterSpacing: 2
                text: "发送(S)"
                FontLoader {
                    id: chineseFont
                    source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                }
                font.family: chineseFont.name;
            }

            MouseArea{
                id: chatMouseArea
                anchors.centerIn: parent
                anchors.fill: parent
                hoverEnabled: true;

                /* 放按钮变色效果 */
                onEntered: {
                    chatSendText.color = "white";
                    chatTextSendButton.color = "#4f4f4f"
                    chatTextSendButton.border.color = "#4f4f4f"
                }
                onExited:  {
                    chatSendText.color = "#4f4f4f";
                    chatTextSendButton.color = "#efefef"
                    chatTextSendButton.border.color = "#afafaf"
                }
            }
        }
    }
}
