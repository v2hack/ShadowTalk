/*
 *  文件: main.qml
 *  功能: 主窗口按钮UI布局
 *  作者: 南野
 *  时间: 2015年7月13日
 */

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0
import QtMultimedia 5.0

Rectangle {
    id: baseWindows;
    objectName: "RootBaseWindow";

    function setBaseWindowVisible() {
        baseWindows.visible = true;
    }
    function setBaseWindowUnvisible() {
        baseWindows.visible = false;
    }
    width: 900
    height: 650
    Drag.active: true
    color: "transparent"

    /* 主窗口可见 */
    visible: true
    /* 透明度 */
    //    opacity: 0.97

    /* 主窗口鼠标拖拽 */
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "10,10"

        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y);
        }
        onPositionChanged: {
            /* 鼠标偏移量 */
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y);
            mainwindow.setX(mainwindow.x + delta.x);
            mainwindow.setY(mainwindow.y + delta.y);
        }
    }

    Rectangle {
        id: shadowWindow
        width: baseWindows.width - 4
        height: baseWindows.height - 4
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        border.color: "white"
        color: "#444"

        layer.enabled: true
        layer.effect: DropShadow {
            radius: 4
            samples: radius * 2
            source: shadowWindow
            color: Qt.rgba(0, 0, 0, 0.8)
            transparentBorder: true
        }
    }

    /* 主窗口按钮 */
    MainWindowButton {
        id: mainButton;
        width: shadowWindow.width - 300
        height: 40;
        anchors.right: shadowWindow.right
        anchors.rightMargin: 3
        anchors.top: shadowWindow.top
        anchors.topMargin: 0
        color: "#efefef"
        opacity: 1
        z:100
    }

    /* 主窗口 */
    Rectangle {
        id: secondLayerWindows
        width: shadowWindow.width
        height: shadowWindow.height
        smooth: true
        anchors.left: shadowWindow.left;
        anchors.top: shadowWindow.top;
        property int fix_width: 296
        color: "#efefef"

        signal send();

        property int changeFlat: 0

        Component.onCompleted: {
            selectChatArea.clicked.connect(send);
            selectUserArea.clicked.connect(send);
        }

        onSend: {
            if (changeFlat === 0) {
                friendList.visible = true;
                chatList.visible = false;
            } else {
                friendList.visible = false;
                chatList.visible = true;
            }
        }

        MediaPlayer {
            id: soundEvet
            autoLoad: true;
            source: "qrc:/sound/event.wav"
        }

        /* 背景 */
        Component {
            id: backGroundComponent;
            Rectangle {
                id: backGroundRectangle
                width: secondLayerWindows.fix_width;
                height: secondLayerWindows.height;
                color: "#2c2c2c"
            }
        }

        /* 导入背景 */
        Loader {
            id: backGroundLoader;
            anchors.top: parent.top;
            anchors.left: parent.left;
            sourceComponent: backGroundComponent;
        }

        Rectangle {
            id: thirdLayerWindow
            width: secondLayerWindows.fix_width;
            height: 144
            color: "#343434"
            z: 700
            anchors {
                top: parent.top
                left: parent.left
            }
            /* 软件图标 */
            Image {
                id: softwareIcon
                height: 25
                width: 25
                anchors {
                    top: parent.top
                    topMargin: 12
                    left: parent.left;
                    leftMargin: 20;
                }
                source: "qrc:/img/st_icon.png";
                fillMode: Image.PreserveAspectFit
                z:200
            }

            /* 软件设置 */
            Image {
                id: softwareSetting
                height: 25
                width: 25
                anchors {
                    top: parent.top
                    topMargin: 12
                    left: softwareIcon.left;
                    leftMargin: 230;
                }
                source: "qrc:/img/st_setting.png";
                fillMode: Image.PreserveAspectFit
                z:200
            }

            /* 选择聊天列表 */
            Image {
                id: selectChat;

                height: 28
                width: 28
                anchors {
                    top: searchLoader.bottom
                    topMargin: 25
                    left: parent.left;
                    leftMargin: 50;
                }
                source: "qrc:/img/st_select_chat.png";
                fillMode: Image.PreserveAspectFit
                z:200

                MouseArea {
                    id: selectChatArea
                    anchors.fill: parent;
                    hoverEnabled: true;

                    onClicked: {
                        selectChat.source = "qrc:/img/st_select_chat_t.png";
                        selectUser.source = "qrc:/img/st_select_users.png";
                        secondLayerWindows.changeFlat = 1;
                        soundEvet.play();
                    }
                }
            }

            /* 水平分割线 */
            Rectangle {
                id: splintLine1
                color: "#282828"
                width: 2
                height: 35
                anchors {
                    top: searchLoader.bottom
                    topMargin: 25
                    left: selectChat.left;
                    leftMargin: 95;
                }
            }

            /* 选择用户列表 */
            Image {
                id: selectUser;
                height: 28
                width: 28
                anchors {
                    top: searchLoader.bottom
                    topMargin: 25
                    left: selectChat.left;
                    leftMargin: 160;
                }
                source: "qrc:/img/st_select_users_t.png";
                fillMode: Image.PreserveAspectFit
                z:200

                MouseArea {
                    id: selectUserArea
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onClicked: {
                        selectUser.source = "qrc:/img/st_select_users_t.png";
                        selectChat.source = "qrc:/img/st_select_chat.png";
                        secondLayerWindows.changeFlat = 0;
                        soundEvet.play();
                    }
                }
            }

            /* 搜索组件 */
            Component {
                id: searchComponent;
                Rectangle {
                    id: searchRectangle
                    width: Math.round(250)
                    height: Math.round(26)
                    radius: 3
                    color: "#515050"

                    Image {
                        id: searchButton;
                        height: 16
                        width: 26
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left;
                            leftMargin: 5;
                        }
                        source: "qrc:/img/st_button_search.png";
                        fillMode: Image.PreserveAspectFit
                    }

                    FontLoader {
                        id: chineseFont
                        source: "qrc:/res/fonts/方正兰亭刊黑_GBK.ttf"
                    }

                    /* 搜索内容输入 */
                    TextArea {
                        id: searchTextEdit;
                        objectName: "SearchTextEdit"

                        function searchTextIsEmpty() {
                            if (searchTextEdit.text == "") {
                                return 1;
                            } else {
                                return 0;
                            }
                        }

                        function setSearchUnvisible() {
                            searchDisplay.visible = false;
                        }

                        function setSearchVisible() {
                            searchDisplay.visible = true;
                        }

                        function searchTextContent() {
                            return searchTextEdit.text;
                        }

                        function searchClearContent() {
                            searchTextEdit.cursorPosition = 0;
                            searchTextEdit.text = "";
                        }

                        height: 26
                        width: 220
                        anchors {
                            top: parent.top
                            left: parent.left
                            leftMargin: 30
                        }
                        anchors.fill: searchRectangle;
                        wrapMode: Text.WrapAnywhere
                        selectByMouse: true
                        backgroundVisible: false
                        frameVisible: false
                        font.family: chineseFont.name;
                        focus: true
                        textColor: "white"

                        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

                        Keys.onReturnPressed: {
                            if (searchTextEdit.text != "") {
                                searchDisplay.visible = true
                            } else {
                                searchDisplay.visible = false
                            }
                        }
                    }
                }
            }

            /* 搜索栏 */
            Loader {
                id: searchLoader;
                anchors {
                    top: parent.top;
                    topMargin: 50
                    left: parent.left
                    leftMargin: (secondLayerWindows.fix_width - 250)/2
                }
                sourceComponent: searchComponent;
            }

            /* 垂直分割线 */
            Rectangle {
                id: splintLine2
                color: "#282828"
                width: secondLayerWindows.fix_width
                height: 2
                anchors {
                    bottom: thirdLayerWindow.bottom;
                    left: parent.left
                }
            }
        }

        /* 好友列表  */
        Rectangle {
            id: friendList
            visible: true

            anchors {
                top: thirdLayerWindow.bottom;
                topMargin: 1
                left: parent.left
            }
            width: secondLayerWindows.fix_width;
            height: parent.height - 140;
            color: "transparent"

            /* 好友列表细节动态 */
            FriendList {
                id: friendListDisplay;
                height: parent.height - 2;
                width: parent.width
                anchors {
                    top: friendList.top
                    left:friendList.left
                }
            }
            z: 220
        }

        /* 聊天列表  */
        Rectangle {
            id: chatList
            visible: false
            anchors {
                top: thirdLayerWindow.bottom;
                topMargin: 1
                left: parent.left
            }
            width: secondLayerWindows.fix_width;
            height: parent.height - 140;
            color: "transparent"

            /* 聊天列表细节动态 */
            ChatList {
                id: chatListDisplay;
                height: parent.height - 2;
                width: parent.width
                anchors {
                    top: chatList.top
                    left:chatList.left
                }
            }
            z: 220
        }

        /* 文字输入对话框 */
        ChatTextInput {
            layer.enabled: false
            id: chatTextInputWindow;
            height: 200 - 4;
            width: shadowWindow.width - secondLayerWindows.fix_width - 2;

            anchors {
                left: backGroundLoader.right;
                bottom: backGroundLoader.bottom;
            }
        }

        /* 聊天内容 */
        ChatDisplay {
            id: chatContent;
            height: shadowWindow.height - chatTextInputWindow.height - 45;
            width: shadowWindow.width - secondLayerWindows.fix_width - 2;
            anchors {
                left:backGroundLoader.right;
                bottom: chatTextInputWindow.top;
            }
        }

        /* 搜索结果显示框 */
        Rectangle {
            id: searchDisplay
            visible: false

            anchors {
                top: secondLayerWindows.top;
                topMargin: 78
                left: parent.left
            }
            width: secondLayerWindows.fix_width;
            height: 400;
            color: "#464646"
            opacity: 0.9

            /* 聊天列表细节动态 */
            SearchList {
                id: searchListDisplay;
                height: parent.height;
                width: parent.width
                anchors {
                    top: searchDisplay.top
                    left:searchDisplay.left
                }
            }
            z: 1000
        }
    }

}
