/*
 *  文件: login.qml
 *  功能: 登陆窗口
 *  作者: 南野
 *  时间: 2015年7月13日
 */

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

Rectangle {
    id: loginWindow;
    height: 600
    width: 940
    color: "transparent"

    Rectangle {
        id: loginQrWindow;
        width: Math.round(245)
        height: Math.round(330)
        radius: 5;
        color: "#efefef"
        opacity: 0.97
        z:500

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        /* 二维码图片 */
        Image {
            id: qrCodeImage
            height: 180
            width: 180
            source: "qrc:/img/st_qr_code.png";
            fillMode: Image.PreserveAspectFit

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 42
            }

            /* 二维码动画区域 */
            MouseArea {
                id: hintImageArea
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: {
                    hintImageAnim1.start();
                }
                onExited: {
                    hintImageAnim2.start();
                }
            }
        }

        /* 二维码提示图片 */
        Image {
            id: hintImage
            height: 600
            width: 330
            source: "qrc:/img/st_qr_hint.png";
            anchors {
                left: qrCodeImage.right
                leftMargin: 45
                verticalCenter: parent.verticalCenter
            }
            z:500
            opacity: 0

            /* 提示图片的动画效果 */
            NumberAnimation {
                id: hintImageAnim1
                target: hintImage
                property: "opacity"
                duration: 800
                easing.type: Easing.InOutQuad
                to: 1
            }
            NumberAnimation {
                id: hintImageAnim2
                target: hintImage
                property: "opacity"
                duration: 800
                easing.type: Easing.InOutQuad
                to: 0
            }

        }

        /* 二维码的文字显示 */
        Text {
            id: companyName
            text: "沙话";
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: qrCodeImage.bottom
                topMargin: 17;
            }
            color: "#4f4f4f"
            font.pixelSize: 14
            font.bold: true
            font.family: "Cronyx"
            font.letterSpacing: 2
        }

        Text {
            id: recommodWord;
            text: "手机扫描二维码登陆";
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: companyName.bottom
                topMargin: 25;
            }
            color: "#4f4f4f"
            font.pixelSize: 14
            font.bold: true
            font.family: "Cronyx"
            font.letterSpacing: 2
        }

        Rectangle {
            id: windowCloseButton
            height: 20
            width: 20
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 10
            color: parent.color

            Image {
                id: closeButtonImage;
                height: 11
                width: 11
                source: "qrc:/img/st_button_close_1.png";
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                id: closeButtonArea
                anchors.fill: parent;
                hoverEnabled: true;

                onClicked: {
                    loginwindow.close()
                }
                onEntered: {
                    closeButtonImage.source = "qrc:/img/st_button_close_2.png"
                }
                onExited: {
                    closeButtonImage.source = "qrc:/img/st_button_close_1.png"
                }
            }
        }
    }
}
