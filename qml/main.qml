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
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import QtMultimedia 5.0
import st.info.GoSearch 1.0
import "js_st_const.js" as JSConst;


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
    visible: true


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

    /* 主窗口的背影 */
    Rectangle {
        id: shadowWindow
        width: baseWindows.width - 4
        height: baseWindows.height - 4
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        border.color: "white"
        color: "transparent"

        layer.enabled: true
        layer.effect: DropShadow {
            radius: 4
            samples: radius * 2
            source: shadowWindow
            color: Qt.rgba(0, 0, 0, 0.8)
            transparentBorder: true
        }
    }

    MediaPlayer {
        id: soundEvet
        autoLoad: true;
        source: "qrc:/sound/event.wav"
    }

    signal send();
    property int changeFlat: 0

    Component.onCompleted: {
        selectChatArea.clicked.connect(send);
        selectUserArea.clicked.connect(send);
        showContent(1);
        friendList.visible = true;
        chatList.visible = false;
    }

    onSend: {
        if (changeFlat === 0) {
            friendList.visible = true;
            chatList.visible = false;
            friendList.goFirst();
        } else {
            friendList.visible = false;
            chatList.visible = true;
        }
    }


    GoSearch{
        id:goSearch;
    }

    /* 搜索组件 */
    Component {
        id: searchComponent;
        Rectangle {
            id: searchRectangle
            width: Math.round(220)
            height: Math.round(26)
            radius: 8
            color: "white"
            border.width : 2
            border.color : "#dcdcdc"
            property bool canSearch: false;
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
                source: "qrc:/res/fonts/fangzheng_gbk.ttf"
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
                function searchTextContent() {
                    return searchTextEdit.text;
                }

                function searchClearContent() {
                    searchTextEdit.cursorPosition = 0;
                    searchTextEdit.text = "";
                }

                height: 26
                width: 190
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
                textColor: "black"
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                onTextChanged: {
                    if (canSearch) {
                        if (searchTextEdit.text != "") {
                            goSearch.goSearchFriend(searchTextEdit.text);
                        } else {
                            goSearch.goLoadAllFriend();
                        }
                    }
                }
                Keys.onPressed: {
                    canSearch=true;
                }
            }
        }
    }    
    /* 标题栏 */
    Rectangle {
        id: mainWindowTitle
        anchors {
            top: shadowWindow.top
            left: shadowWindow.left;
        }
        color: '#ededed';
        width: shadowWindow.width;
        height: 45;
        //logo
        Image{
             id:main_img_title_logo;
             anchors.left: parent.left;
             anchors.top:parent.top;
             anchors.topMargin: 10;
             width: 80;
             height:30;
             source: JSConst.main_res_png_title_logo;
             fillMode: Image.PreserveAspectFit
             clip:true;
             visible: false;
        }

        /* 搜索栏 */
        Loader {
            id: searchLoader;
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 70
            }
            sourceComponent: searchComponent;
        }

        /* 窗口按钮 */
        MainWindowButton {
            id: mainButton;
            width: mainWindowTitle.width - 300
            height: 40;
            anchors.right: mainWindowTitle.right
            anchors.rightMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            color: "#efefef"
            opacity: 1
            z:100
        }

        /* 分割线 */
        Rectangle {
            id: titleSpilteLine
            color: "#dcdcdc"
            width: parent.width;
            height: 1;
            anchors {
                bottom: parent.bottom
                left: parent.left;
            }
        }
    }


    /* 窗口选择栏 */
    Rectangle {
        id: selectWindowColumn
        anchors {
            top: mainWindowTitle.bottom
            left: shadowWindow.left;
        }
        color: '#3b3b43';
        width: 55;
        height: shadowWindow.height - mainWindowTitle.height;

        ColumnLayout {
            spacing: 1
            anchors.fill: parent

            Image {
                id: selectChat;
                anchors {
                    top: parent.top
                    topMargin: 25
                }

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 28
                Layout.preferredHeight: 28

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
                        showContent(0);     //显示聊天界面
                        baseWindows.changeFlat = 1;
                        soundEvet.play();
                    }
                }
            }

            /* 选择用户列表图片 */
            Image {
                id: selectUser;
                anchors {
                    top: selectChat.bottom
                    topMargin: 25
                }
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 28
                Layout.preferredHeight: 28

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
                        showContent(0);   //显示聊天界面
                        baseWindows.changeFlat = 0;
                        soundEvet.play();
                        friendList.goFirst();
                    }
                }
            }
        }
    }

    /* 联系人列表和会话列表 */
    Rectangle {
        id: selectContactColumn
        color: '#ffffff';
        width: 250;
        height: shadowWindow.height - mainWindowTitle.height - 1;

        anchors {
            top: mainWindowTitle.bottom
            left: selectWindowColumn.right;
        }

        Rectangle
        {
            id: friendList
            visible: true
            width: parent.width;
            height: parent.height;
            color: "transparent"
            anchors.fill: parent
            FriendList {
                id: friendListDisplay;
                height: parent.height;
                width: parent.width
                anchors {
                    top: friendList.top
                    left:friendList.left
                }
            }
            z: 220
            function goFirst(){
                friendListDisplay.goFirst();
            }
            clip:true;
        }

        Rectangle
        {
            id: chatList
            visible: true
            width: parent.width;
            height: parent.height;
            color: "transparent"
            anchors.fill: parent
            clip:true;
            /* 聊天列表细节动态 */
            ChatList {
                id: chatListDisplay;
                height: parent.height;
                width: parent.width
                anchors {
                    top: chatList.top
                    left:chatList.left
                }
            }
            z: 220
        }
    }

    /* 分割线 */
    Rectangle {
        id: vSpliteColumn
        color: '#dcdcdc';
        width: 1;
        height: shadowWindow.height - mainWindowTitle.height - 1;
        anchors {
            top: mainWindowTitle.bottom
            left: selectContactColumn.right;
        }
    }

    function showContent(itype){
        JSConst.showLog("showContent-------------------:"+itype);
       if (itype===JSConst.main_itype_blankselect){
          messageblank.visible=false;
          messageColumn.visible=true;
       }
       if(itype===JSConst.main_itype_columnselect){
           messageblank.visible=true;
           messageColumn.visible=false;
       }
       if(itype===JSConst.main_itype_friendListselect){
           messageblank.visible=false;
           messageColumn.visible=true;
           friendList.visible = true;
           chatList.visible = false;
       }
    }

    Rectangle{
        id:messageblank;
        color: '#f0f0f0';
        width: baseWindows.width - selectWindowColumn.width - selectContactColumn.width - 5;
        height: shadowWindow.height - mainWindowTitle.height - 2;
        anchors {
            top: mainWindowTitle.bottom
            left: vSpliteColumn.right;
        }
        visible: false;
        ColumnLayout {
            spacing: 0
            anchors.fill: parent
            /*聊天的空白页*/
            STChatBlank{
                id:chatBlank;
                anchors.top:parent.top
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: messageColumn.width
                Layout.preferredHeight: messageColumn.height - 196
                clip:true;
            }
        }
    }

    /* 消息栏输入栏  */
    Rectangle {
        id: messageColumn
        color: '#f0f0f0';
        width: baseWindows.width - selectWindowColumn.width - selectContactColumn.width - 5;
        height: shadowWindow.height - mainWindowTitle.height - 2;
        anchors {
            top: mainWindowTitle.bottom
            left: vSpliteColumn.right;
        }
        visible: true;
        function addTestContent(str){
            chatContent.addTestMsg(str);
        }
        ColumnLayout {
            spacing: 0
            anchors.fill: parent
            /* 聊天内容 */
            STChatView {
                id: chatContent;
                anchors {
                    top: parent.top                    
                }
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: messageColumn.width
                Layout.preferredHeight: messageColumn.height - 196
                clip:true;                
            }
            /* 分割线 */
            Rectangle {
                id: hSpliteColumn
                color: '#dcdcdc';
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: messageColumn.width
                Layout.preferredHeight: 1
                visible:false;
                anchors {
                    top: chatContent.bottom
                }
            }

            /* 文字输入对话框 */
            STChatInput {
                layer.enabled: false
                id: chatTextInputWindow;
                anchors {
                    top: hSpliteColumn.bottom                    
                }
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: messageColumn.width
                Layout.preferredHeight: 196                
            }
        }
    }
}
