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

    Rectangle {
        id: chatTextEditRectangle;
        width: parent.width;
        height: parent.height - chatTool.height;
        color: "#efefef"

        anchors {
            top: chatTool.bottom;
        }
        /* 输入编辑栏 */
        TextInput {
            id: chatTextEdit;
            anchors.fill: chatTextEditRectangle;
            wrapMode: Text.Wrap
        }
    }
}
