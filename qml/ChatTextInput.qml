/*
 *  文件: ChatTextInput.qml
 *  功能: 聊天输入框
 *  作者: 南野
 *  时间: 2015年7月20日
 */
import QtQuick 2.4
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Rectangle {
    id: chatTextInput
    z:400

    /* 输入工具栏 */
    Rectangle {
        id: chatTool
        width: parent.width;
        height: 29;

        /* 表情按钮 */
        Rectangle {
            id: chatExpressionRectangle;
            width: 25

            anchors {
                top: parent.top;
                topMargin: 2;
                left: parent.left;
                leftMargin: 6
            }

            Image {
                id: expressionImage;
                height: 25
                width: 25
                source: "qrc:/img/st_chat_expression.png";
                fillMode: Image.PreserveAspectFit
            }
            MouseArea{
                anchors.centerIn: parent
                anchors.fill: parent
                hoverEnabled: true;

                onClicked: { /*TODO*/ }
                onEntered: {          }
                onExited:  {          }
            }
        }

        /* 截图按钮 */
        Rectangle {
            id: screenshotRectangle;
            height: parent.height
            width: 25

            anchors {
                top: parent.top;
                topMargin: 2;
                left: chatExpressionRectangle.right;
                leftMargin: 6
            }

            Image {
                id: screenshotImage;
                height: 25
                width: 25
                source: "qrc:/img/st_chat_screenshot.png";
                fillMode: Image.PreserveAspectFit

                MouseArea{
                    anchors.centerIn: parent
                    anchors.fill: parent
                    hoverEnabled: true;

                    onClicked: { /*TODO*/ }
                    onEntered: {          }
                    onExited:  {          }
                }
            }
        }

        /* 发送按钮 */
        Rectangle {
            id: deliveryRectangle;
            height: parent.height
            width: 25

            anchors {
                top: parent.top;
                topMargin: 2;
                left: screenshotRectangle.right;
                leftMargin: 6
            }
            Image {
                id: deliveryImage;
                height: 25
                width: 25
                source: "qrc:/img/st_chat_delivery.png";
                fillMode: Image.PreserveAspectFit

                MouseArea{
                    anchors.centerIn: parent
                    anchors.fill: parent
                    hoverEnabled: true;

                    onClicked: { /*TODO*/ }
                    onEntered: {          }
                    onExited:  {          }
                }
            }
        }
    }


    /* 发送消息链接 */
    Connections {
        target: chatMouseArea

        onClicked: {
            /* 清理数据需要恢复光标的位置 */
            chatTextEdit.cursorPosition = 0;
            /* TODO: 这里要修改为具体发送消息 */
            chatTextEdit.text = "";
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
            radius: 5

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
                font.family: "Cronyx"
                font.letterSpacing: 2
                text: "发送(S)"
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
