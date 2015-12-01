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
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QtQuick.Layouts 1.1;

import "functions.js" as PinYin
import "common.js" as JsCommon
import "js_st_emoji.js" as EMOJI

/* 导入文字与像素计算类型 */
import st.font.PointSizeToPixelSize 1.0
import st.info.Voice 1.0
import st.info.NormalPicture 1.0

Rectangle {
    id: messageRectangle;
    color: "#efefef"

    property int wordsType: 1
    property int imageType: 2
    property int voiceType: 3    

    /* 消息提示声音 */
    MediaPlayer {
        id: soundMessage
        objectName: "MessageSound"
        autoLoad: true;
        source: "qrc:/sound/message.wav"

        function playMessageSound() {
            soundMessage.play();
        }
    }

    /* 播放语音 */
    MediaPlayer {
        id: voiceMessage
        objectName: "MessageVoice"
        source: ""

        function playMessageVoice(voiceFile) {
            voiceMessage.source = voiceFile
            voiceMessage.play();
        }
        function stopMessageVoice() {
            voiceMessage.stop();
        }
    }

    Rectangle {
        id: chatLine
        anchors {
            top: parent.top
            topMargin: -5
            left: parent.left;
            leftMargin: 1
        }
        width: parent.width;
        height: 1;
        opacity: 0
        color: "#979797"

        Behavior on opacity {
            NumberAnimation {
                duration: 600
            }
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
                duration: 80
            }
            NumberAnimation {
                property: "scale";
                from: 0;
                to: 1.0;
                duration: 80
            }
        }
        displaced: Transition {
            NumberAnimation {
                properties: "x,y";
                duration: 150;
                easing.type: Easing.OutBounce
            }
        }

        /* c++调用: 添加消息
         * 这里item是QVariant类型：包含
         * index、name、dataType、dircect、userMesssage、messageIndex
         */
        function getMsgHeight_(data){
            var mHeight=0;
            if (data.dataType === wordsType){
                var countLen=EMOJI.countStrLength(data.msgContent, parseInt(data.emojiCount));
                var arrstr=countLen.split("@@");
                mHeight=parseInt(arrstr[1]);
            }
            return mHeight + 30;
        }

        function addMessage(data) {
            var str=data.userMessage;
            str=EMOJI.getEMOmap(str);
            var arrstr=str.split("@*@");         
            data.emojiCount=arrstr[2];
            data.userMessage=arrstr[0];
            data.msgContent=arrstr[1];
            model.append(data);
            var height =  JsCommon.getMessageFrameHeight(
                        getPixelSize.height(10),
                        getPixelSize.width(10 , data.msgContent),
                        250);
            if (data.dataType === imageType) {
                messageView.contentY += data.pictureHeight + (150);
            } else {
                messageView.contentY += getMsgHeight_(data) + 100;
            }            
        }
        /* c++调用:清除消息 */
        function clearMessage() { model.clear(); }
        /* c++调用:删除一个消息
         * 这里item是QVariant类型：包含 index、count成员
         */
        function removeMessage(item) {
            model.remove(parseInt(item.index),  parseInt(item.count));
        }

        /* c++调用: 设置图片显示 */
        function setFriendImage(index, picturePath) {
            model.setProperty(index, "userPicture", picturePath);
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
            anchors.topMargin: 4;
            function getItemHeight() {
                var height =  JsCommon.getMessageFrameHeight(
                            getPixelSize.height(10),
                            getPixelSize.width(10 , msgContent), 250);
                var row_num = height/17;
                console.log("c++ fun:getItemHeight()______:"+(row_num * 17) + 10 + 40);
                return (row_num * 17) + 10 + 40;
            }
            function getMsgHeight(){
                var mHeight=0;
                if (dataType == wordsType){
                    var countLen=EMOJI.countStrLength(msgContent,parseInt(emojiCount));
                    var arrstr=countLen.split("@@");
                    mHeight=parseInt(arrstr[1]);
                }
                return mHeight+30;
            }

            height: {
                if (dataType == wordsType) { return getMsgHeight() + 10;     }
                if (dataType == voiceType) { return 90;                  }
                if (dataType == imageType) { return pictureHeight + 100; }
            }
            width: parent.width;

            /* C++ 计算像素的类 */
            PointSizeToPixelSize {id: getPixelSize;}
            Voice {id: playVoice;}
            NormalPicture {id: displayPicture}

            /* 消息框上边缘的动态效果 */
            MouseArea {
                id: showChatLineArea
                anchors.fill: parent
                onReleased: {
                    chatLine.state = "hideLine";
                }
                z:900
            }
            states: [
                State {
                    name: "showLine"
                    when: messageView.draggingVertically
                    changes: [
                        PropertyChanges {
                            target: chatLine;
                            opacity: 0.3
                        }
                    ]
                },
                State {
                    name: "hideLine"
                    changes: [
                        PropertyChanges {
                            target: chatLine;
                            opacity: 0
                        }
                    ]
                }
            ]
            state: "hideLine"


            Rectangle {
                z: 1000
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
                    color: direct === 0 ? JsCommon.getColor(name) : "#508cc0";

                    anchors {
                        top: parent.top
                        topMargin: 5
                        left:  direct === 0 ? parent.left : undefined
                        leftMargin: direct === 0 ? 14 : undefined
                        right: direct === 1 ? parent.right : undefined
                        rightMargin: direct === 1 ? 14 : undefined
                    }

                    /* 好友名字 */
                    Text {
                        id: friendItemName
                        anchors {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                        }
                        color: "white"
                        font.pixelSize: 15
                        text: direct === 0 ? JsCommon.getShortName(name) : "我"
                        font.bold: true
                        font.letterSpacing: 1

                        //字体先注释，编译太慢
                        FontLoader {
                            id: chineseFont
                            source: "qrc:/res/fonts/fangzheng_gbk.ttf"
                        }
                        font.family: chineseFont.name;
                    }

                    /* 对话框小箭头 */
                    Image {
                        id: friendMessagePointImage
                        width: 20
                        height: 20

                        anchors {
                            top: parent.top
                            topMargin: 8
                            left: direct === 0 ? friendItemIcon.right : undefined
                            leftMargin: direct === 0 ? 2 : undefined
                            right: direct == 1 ? friendItemIcon.left : undefined
                            rightMargin: direct === 1 ? 5 : undefined
                        }
                        source: {
                            if (direct === 0) {
                                return "qrc:/img/st_white_point.png";
                            } else {
                                return "qrc:/img/st_green_point.png"
                            }
                        }
                        fillMode: Image.PreserveAspectFit
                    }


                    /* 消息内容 */
                    Rectangle {
                        id: friendMessageContent
                        Layout.minimumHeight: 20;
                        Layout.minimumWidth: 20;
                        radius: 3                        

                        function getMessageHeight() {                            
                            var height =  JsCommon.getMessageFrameHeight(
                                        getPixelSize.height(10),
                                        getPixelSize.width(10 , msgContent), 250);
                            return height + 20
                        }

                        function getMessageWidth() {
                            var width = JsCommon.getMessageFrameWidth(
                                        getPixelSize.width(10, msgContent)) + 20;
                            return width + 10;
                        }

                        function getMsgHeight(){
                            var mHeight=0;
                            if (dataType == wordsType){
                                var st_max_width=280;
                                var countLen=EMOJI.countStrLength(msgContent,parseInt(emojiCount));
                                var arrstr=countLen.split("@@");
                                mHeight=parseInt(arrstr[1]);
                            }
                            return mHeight;
                        }
                        function getMsgWidth(){
                            var mWidth=0;
                            if (dataType == wordsType){
                                var st_max_width=260;
                                var countLen=EMOJI.countStrLength(msgContent,parseInt(emojiCount));
                                var arrstr=countLen.split("@@");
                                mWidth=parseInt(arrstr[0]);
                                if (mWidth<=st_max_width){
                                    mWidth=mWidth;
                                }else
                                {
                                    mWidth=260;
                                }
                            }
                            return mWidth+10;
                        }
                        height: {
                            if (dataType == wordsType) {                   
                                return getMsgHeight() + 10;
                            }
                            if (dataType == voiceType) { return 35                  }
                            if (dataType == imageType) { return pictureHeight + 10; }
                        }
                        width: {
                            if (dataType == wordsType) {
                                return getMsgWidth();
                            }
                            if (dataType == voiceType) {
                                if (voiceSeconds < 10) {
                                    return 70;
                                } else {
                                    if ((70 + voiceSeconds) > 150) {
                                        return 150
                                    } else {
                                        return 70 + voiceSeconds
                                    }
                                }
                            }
                            if (dataType == imageType) { return pictureWidth + 10;  }
                        }

                        anchors {
                            top: parent.top
                            topMargin: 7
                            left: direct === 0 ? friendMessagePointImage.right : undefined
                            leftMargin:  direct === 0 ? -3 : undefined
                            right: direct === 1 ? friendMessagePointImage.left : undefined
                            rightMargin: direct === 1 ? -5 :undefined
                        }

                        /* 透明颜色背景 */
                        Rectangle {
                            id: freindMessageContenColor;
                            color: direct === 0 ?  "white" : "#b4eb7c"
                            radius: 3
                            width: friendMessageContent.width
                            height: friendMessageContent.height;
                            anchors.fill: friendMessageContent
                        }

                        /* 语音显示 */
                        Rectangle {
                            id: friendMessageVoice

                            visible: dataType == voiceType ? true : false
                            color: "transparent"
                            radius: 3

                            anchors {
                                fill: friendMessageContent
                                left:parent.left
                                leftMargin: 10
                            }

                            Image {
                                id: voiceImage1
                                height : 22
                                width: 22
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                }
                                source: direct === 0 ? "qrc:/img/sound/st_m_sound_1.png" : "qrc:/img/sound/st_m_sound_11.png"
                                fillMode: Image.PreserveAspectFit
                                mirror: direct === 0 ? false : true
                            }
                            Image {
                                id: voiceImage2
                                height : 22
                                width: 22
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                }
                                source: direct === 0 ? "qrc:/img/sound/st_m_sound_2.png" : "qrc:/img/sound/st_m_sound_22.png"
                                fillMode: Image.PreserveAspectFit
                                mirror: direct === 0 ? false : true
                            }
                            Image {
                                id: voiceImage3
                                height : 22
                                width: 22
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                }
                                source: direct === 0 ? "qrc:/img/sound/st_m_sound_3.png"  : "qrc:/img/sound/st_m_sound_33.png"
                                fillMode: Image.PreserveAspectFit
                                mirror: direct === 0 ? false : true
                            }

                            Text {
                                id: voicePlaySeconds;
                                text: voiceSeconds + "s"
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    right: parent.right
                                    rightMargin: 8
                                }
                                font.family: chineseFont.name;
                            }

                            /* 顺序播放 */
                            SequentialAnimation {
                                id: voiceAnim
                                function stopVoiceAnim() {
                                    voiceAnim.stop();
                                    voiceImage1.opacity = 1;
                                    voiceImage2.opacity = 1;
                                    voiceImage3.opacity = 1;
                                }

                                NumberAnimation {
                                    target: voiceImage1
                                    property: "opacity"
                                    from: 1
                                    to: 0
                                    duration: 1
                                }
                                NumberAnimation {
                                    target: voiceImage2
                                    property: "opacity"
                                    from: 1
                                    to: 0
                                    duration: 1
                                }
                                NumberAnimation {
                                    target: voiceImage3
                                    property: "opacity"
                                    from: 1
                                    to: 0
                                    duration: 1
                                }
                                NumberAnimation {
                                    target: voiceImage1
                                    property: "opacity"
                                    from: 0
                                    to: 1.0
                                    duration: 120
                                }
                                NumberAnimation {
                                    target: voiceImage2
                                    property: "opacity"
                                    from: 0
                                    to: 1.0
                                    duration: 240
                                }
                                NumberAnimation {
                                    target: voiceImage3
                                    property: "opacity"
                                    from: 0
                                    to: 1.0
                                    duration: 360
                                }
                                PauseAnimation {
                                    duration: 200
                                }
                                loops: voiceSeconds + 1
                            }

                            /* 点击播放语音 */
                            MouseArea {
                                property int playSwitch: 0
                                anchors.centerIn: parent
                                anchors.fill: parent
                                onClicked: {
                                    if (playSwitch === 0) {
                                        playVoice.playVoice(uid, messageIndex);
                                        playSwitch = 1;
                                        voiceAnim.start();
                                    } else {
                                        playVoice.stopVoice();
                                        playSwitch = 0;
                                        voiceAnim.stopVoiceAnim();
                                    }
                                }
                            }
                            z:1000
                        }

                        /* 文字显示 */
                        TextWithImage {
                            id: friendMessageText                
                            anchors.fill: parent;
                            anchors.topMargin: 4;
                            anchors.leftMargin: 4;
                            anchors.rightMargin: 2;
                            Layout.fillWidth: true;
                            text: dataType == wordsType ? userMessage : ""                            
                            wrapMode: Text.WrapAnywhere;
                            textFormat : Text.RichText;
                            color: "black"
                            font.pointSize: 10                                                        
                            verticalAlignment: Text.AlignJustify;
                            horizontalAlignment: Text.AlignJustify;
                            visible: dataType == wordsType ? true : false
                            font.family: chineseFont.name;
                        }

                        /*  图片显示 */
                        Image {
                            id: friendMessagePicture
                            visible: dataType == imageType ? true : false
                            height: pictureHeight + 1
                            width: pictureWidth + 1
                            source: Qt.resolvedUrl(userPicture)
                            fillMode: Image.PreserveAspectFit

                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                            /* 鼠标双击弹出大图 */
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    displayPicture.displayNormalPicture(uid, messageIndex);
                                }
                            }
                        }

                    }
                }
            }
        }
    }
}

