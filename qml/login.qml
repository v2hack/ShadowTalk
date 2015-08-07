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
    width: 1100
    color: "transparent"

    property int loginProcessLoaderFlag: 0

    Rectangle {
        id: loginQrWindow;
        width: Math.round(320)
        height: Math.round(450)
        radius: 5;
        color: "#efefef"
        z:500

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        /* 同步进度条 */
        Rectangle {
            id: qrProcessRect
            height: 300
            width: parent.width
            visible: false
            color : "#efefef"
            anchors {
                top: parent.top
                topMargin: 20
            }

            /* 底色 */
            Rectangle {
                id: qrProcessLayer1
                height: 300
                width: 300
                anchors.fill: qrProcessRect
                color: "#ccc6bf"
            }

            /* 画同步进度组件 */
            LoginProcess {
                id: loginProcessLoader1
                width: qrProcessImage.width
                height: qrProcessImage.height
                anchors {
                    top: parent.top
                    topMargin: -30
                }
                z:510
            }

            /* 进度框 */
            Rectangle {
                id: loginProcessPaint
                objectName: "objectLoginProcessPaint"

                /* c++调用，画进度原型 */
                function processPaint(value) {
                    loginProcessLoader1.gValue = value;
                    loginProcessLoader1.rePaint();
                    loginProcessLoader1.visible = true;
                    loginProcessPercent.text = parseInt(value * 100 /359)  + "%";
                }
            }

            /* 进度图片 */
            Image {
                id: qrProcessImage
                height: 320
                width: 320
                source: "qrc:/img/st_qr_process.png";
                fillMode: Image.PreserveAspectFit

                anchors {
                    top: parent.top
                    topMargin: -10
                }
                z:511
            }

            /* 进度箭头 */
            Image {
                id: qrProcessPoint
                height: 210
                width: 210
                source: "qrc:/img/st_qr_point.png";
                fillMode: Image.PreserveAspectFit
                anchors {
                    verticalCenter: qrProcessImage.verticalCenter
                    horizontalCenter: qrProcessImage.horizontalCenter
                }
                rotation: 0

                states: State {
                    name: "rotated"
                    when: loginProcessLoader1.gValue != 0
                    PropertyChanges {
                        target: qrProcessPoint;
                        rotation: 2 + loginProcessLoader1.gValue;
                    }
                }
                z:511
            }

            Text {
                id: loginProcessPercent
                anchors {
                    top: parent.top
                    topMargin: 112
                    horizontalCenter: parent.horizontalCenter
                }
                font.pixelSize : 60
                font.bold : true
                color: "#00b9fe"
                z: 513
            }
        }

        /* 二维码图片 */
        Image {
            id: qrCodeImage
            height: 250
            width: 250
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
                onClicked: {
                    qrCodeImage.visible = false;
                    qrProcessRect.visible = true;
                    recommodWord.text = "正在同步手机数据";
                }
            }
        }

        /* 二维码提示图片 */
        Image {
            id: hintImage
            height: 550
            width: 300
            source: "qrc:/img/st_qr_hint.png";
            z:500
            opacity: 0

            anchors {
                left: qrCodeImage.right
                leftMargin: 50
                top: parent.top
                topMargin: -50
            }

            /* 提示图片的动画效果 */
            NumberAnimation {
                id: hintImageAnim1
                target: hintImage
                property: "opacity"
                duration: 400
                easing.type: Easing.InOutQuad
                to: 1
            }
            NumberAnimation {
                id: hintImageAnim2
                target: hintImage
                property: "opacity"
                duration: 400
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
                topMargin: 35;
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

        /* 关闭按钮 */
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