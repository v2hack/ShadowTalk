/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatView.qml
 *  简要描述: 聊天内容显示模块
 *
 *  当前版本:1.0
 *  作者: nanye,hsf
 *  日期: 2015-12-2 整理
 *  说明:
 ******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QtQuick.Layouts 1.1
//js脚本
import "functions.js" as PinYin ;
import "common.js" as JsCommon ;
import "js_st_emoji.js" as EMOJI
import "js_st_const.js" as JSConst;

/* 导入文字与像素计算类型 */
import st.font.PointSizeToPixelSize 1.0
import st.info.Voice 1.0
import st.info.NormalPicture 1.0

Item {
    id: messageRectangle;
    clip:true;

    property int wordsType: 1
    property int imageType: 2
    property int voiceType: 3    
    property int ispicture:0;
    property int preitemHeight: 0;
    property int itemHeight: 0;


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
        color: "#f0f0f0"

        Behavior on opacity {
            NumberAnimation {
                duration: 600
            }
        }
    }

        ListModel{
            id:chatModel
            dynamicRoles: true;
        }

        Rectangle{
            id:viewRect
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top:parent.top
            anchors.leftMargin: 10
            anchors.rightMargin: 2
            anchors.topMargin: 10
            anchors.bottomMargin: 10;
            color:"#f0f0f0"
            height: parent.height
            border.width: 0
            border.color: "#f0f0f0"
            radius: 0

            ListView{
                id:chatView
                objectName: "MessageListModel"
                width:parent.width-10
                Layout.maximumWidth: 100;
                anchors.centerIn: viewRect
                height: parent.height-10
                spacing:10
                clip:true
                model:chatModel
                delegate:
                    STChatItem{
                    chatName: chatName1
                    chatContents: chatContents1
                    chatFlag: chatFlag1
                    chatHead: chatHead1
                    chatTime: chatTime1
                    chatIndex: index
                    chatDataType: chatDataType1;
                    chatPicture:chatPicture1;
                    chathasEmoji:chathasEmoji1;
                    chatUid:chatUid1;
                    chatMessageIndex:chatMessageIndex1;
                    chatContentWidth:chatContentWidth1;
                    chatContentHeight:chatContentHeight1;                    
                    chatPictureHeight: chatPictureHeight1;
                    chatPictureWidth: chatPictureWidth1;
                    chatPreItemHeight: chatPreItemHeight1;
                }
                function addMessage(data)
                 {
                     var str=data.userMessage;
                     var msgContent="";
                     str=EMOJI.getEMOmap(str);
                     var arrstr=str.split("@*@");
                     data.emojiCount=arrstr[2];    //表情个数
                     data.userMessage=arrstr[0];   //处理后能显示表情的消息
                     //data.msgContent=arrstr[1];  //处理后测试长度,暂时不用
                    //获取实际的宽和高
                    JSConst.showLogInfo("show data.direct",data.direct);
                    JSConst.showLogInfo("show data.dataType",data.dataType);
                    JSConst.showLogInfo("show data.pictureHeight",data.pictureHeight);
                    JSConst.showLogInfo("show data.pictureWidth",data.pictureWidth);
                    JSConst.showLogInfo("show data.uid",data.uid);
                    JSConst.showLogInfo("show data.messageIndex",data.messageIndex);
                    chatcontentWH.addmsg(data.userMessage);
                    var cwidth=getwidth(data.dataType,data);
                    var cheight=getheight(data.dataType,data);
                    var chat={"chatName1":data.name,
                               "chatHead1":"",
                               "chatFlag1":data.direct,
                               "chatTime1":"",
                               "chatDataType1":data.dataType,
                               "chatPicture1":data.userPicture,
                               "chatContents1":data.userMessage,
                               "chathasEmoji1":parseInt(data.emojiCount),
                               "chatUid1":    data.uid,
                               "chatMessageIndex1":data.messageIndex,
                               "chatvoiceSeconds1":data.voiceSeconds,
                               "chatContentHeight1":cheight,
                               "chatContentWidth1":cwidth,
                               "chatPicture1":data.userPicture,
                               "chatPictureHeight1":(data.pictureHeight===undefined)?0:data.pictureHeight,
                               "chatPictureWidth1":(data.pictureWidth===undefined)?0:data.pictureWidth,
                               "chatPreItemHeight1":itemHeight
                                };
                     chatModel.append(chat);
                     chatView.positionViewAtEnd();
                 }


                 function setitemheight(itype){
                     if (ispicture===1){
                         itemHeight=preitemHeight
                         ispicture=0;
                     } else
                     {
                         itemHeight=0;
                     }
                 }
                 //获取内容外框的宽
                 function getwidth(itype,data){
                    setitemheight(0);
                    if(itype===wordsType){       
                      return chatcontentWH.getWidth();                      
                    }
                    if (itype===imageType){
                        ispicture=1;
                        preitemHeight=data.pictureWidth + 10
                        return preitemHeight;
                    }
                    if (itype===voiceType){
                        if (data.voiceSeconds < 10) {
                            return 70;
                        } else {
                            if ((70 + data.voiceSeconds) > 150) {
                                return 150
                            } else {
                                return 70 + data.voiceSeconds
                            }
                        }
                    }
                 }
                 //获取内容外框的高
                 function getheight(itype,data){
                     if(itype===wordsType){
                       return chatcontentWH.getHeight();
                     }
                     if (itype===imageType){
                        return data.pictureHeight + 10;
                     }
                     if (itype===voiceType){
                        return 35;
                     }
                 }

                 /* c++调用:清除消息 */
                 function clearMessage()
                 {
                     chatModel.clear();
                 }
                 /* c++调用:删除一个消息
                  * 这里item是QVariant类型：包含 index、count成员
                  */
                 function removeMessage(item) {
                     chatModel.remove(parseInt(item.index),  parseInt(item.count));
                 }

                 /* c++调用: 设置图片显示 */
                 function setFriendImage(index, picturePath) {
                     chatModel.setProperty(index, "userPicture", picturePath);
                 }

                 //测试添加消息接口
                 //有空可以单独整理成一个测试单元的文件
                 function addTestMsg(str){
                   chatcontentWH.addmsg(str);
                   var chat={  "chatName1":JSConst.chatitem_myname,
                               "chatHead1":"",
                               "chatContents1":str,
                               "chatFlag1":JSConst.getTestChatFlag(),
                               "chatTime1":"","chatDataType1":0,
                               "chatPicture1":"",
                               "chatSouContents1":str,
                               "chathasEmoji1":1,
                               "chatContentHeight1":chatcontentWH.getHeight(),
                               "chatContentWidth1":chatcontentWH.getWidth()
                         };
                   JSConst.showLog("test show chat content:_____"+str);
                   chatModel.append(chat);
                   chatView.positionViewAtEnd();
                 }
            } 
        }


        STChatScrollBar{
            id:scBar
            anchors.right: viewRect.right
            anchors.rightMargin: 2
            anchors.top: viewRect.top
            anchors.bottom: viewRect.bottom
            width: 5
            scrollColor: "#dbe1e5"
            opacity: 0
            orientation: Qt.Vertical
            position: chatView.visibleArea.yPosition
            pageSize: chatView.visibleArea.heightRatio
            clip: true
        }
        states: State {
            name: "ShowBars"
            when: chatView.movingVertically || chatView.movingHorizontally
            PropertyChanges { target: scBar; opacity: 1 }
        }
        STChatContentWH{
            id:chatcontentWH;
            width: 800
            height: 600
            anchors.fill: parent;
            visible: false;
            color: "white"
        }




}

