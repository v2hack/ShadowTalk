/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatItem.qml
 *  简要描述: 聊天显示每一个聊天的Item
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/
import QtQuick 2.0
import st.info.Voice 1.0
import st.info.NormalPicture 1.0

import "functions.js" as PinYin
import "common.js" as JsCommon
import "js_st_emoji.js" as EMOJIMAP;
import "js_st_const.js" as JSConst;



Rectangle {
    id:stchatitem
    width: parent.width
    height:(getHeight()>48)?getHeight():52
    color: "#f0f0f0"
    property string chatName: "昵称"
    property string chatContents: "内容";
    property string chatHead: "头像"
    property string chatTime: "13819128918"
    property int    chatFlag: 0   //0:myself 1: other
    property int    chatIndex: 0  //序号
    property int    chatDataType: 0  //数据类型
    property string chatSouContents: "";  //聊天内容
    property int    chathasEmoji:0;
    property int    chatVoiceSeconds:0;
    property int    chatUid: 0;
    property int    chatMessageIndex:0;
    property string chatValuemessageData:"";
    property int    chatContentWidth: 200;
    property int    chatContentHeight: 20;
    property string chatPicture: "";
    property int    chatPictureWidth:0;
    property int    chatPictureHeight:0;
    property int    chatPreItemHeight:0;

    function getHeight()
    {
        var iHeight = imgTriangle.height+contents.height+20;
        if (chatDataType==imageType){
           iHeight=imgTriangle.height+chatPictureHeight+20;
        }
        JSConst.showLog("iheight"+iHeight);
        return iHeight;
    }

    Rectangle{
        id:rect_myhead
        color: {
            var c="#7c509d";
            if (chatFlag==1){               
               c =  JsCommon.getColor(chatName);
            }
            if (chatFlag==0)
            {
              c=JSConst.chatitem_send_blue;
            }
           return c
        }

        width: 36;
        height: 36;
        radius: width / 2
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: (chatFlag==1)?10:parent.width-50
        Text{
            id:txt_myName
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
            color: "white";
            text:(chatFlag===0)?JSConst.chatitem_myname:JsCommon.getShortName(chatName);
            font.bold: true
            font.letterSpacing: 1
            font.pixelSize: 15
            FontLoader {
                id: chineseFont
                source: JSConst.chatinput_res_font_fangzheng;
            }
            font.family: chineseFont.name;
        }

    }

    Image {
        id: imgTriangle
        width: 20
        height: 20
        clip:true;
        anchors.right:(chatFlag==1)?rect_myhead.right:rect_myhead.left;
        anchors.rightMargin: (chatFlag==1)?-14:0;
        anchors.top: parent.top;
        anchors.topMargin: rect_myhead.height/2;
        source:{
            if (chatFlag === 0) {
                return JSConst.chatitem_res_png_right;
            } else {
                return JSConst.chatitem_res_png_left;
            }
        }
    }
    //文字图片显示的边框如果空白不够多，可以用以下的方法补充
    Rectangle{
        id:rect_blankR;
        width:2;
        height:chatContentHeight;
        anchors.right: rect_contents.left;
        anchors.top: rect_contents.top
        color: (chatFlag == 0)? JSConst.chatitem_rect_green : "white"
        visible: (chatFlag == 0)?true:false;
    }
    Rectangle{
        id:rect_blankL;
        width:4;
        height:chatContentHeight;
        anchors.left: rect_contents.right;
        anchors.top: rect_contents.top
        color: (chatFlag == 0)? JSConst.chatitem_rect_green : "white"
        visible: false;
        //visible: (chatFlag == 0)?false:true;
    }

    //显示文本和表情
    Rectangle{
        id:rect_contents;
        width: {
            JSConst.showLog("get the width++++++++++++++++++++++："+chatContentWidth);
            return chatContentWidth;

       }
        height: {
           JSConst.showLog("get the Height++++++++++++++++++++++："+chatContentHeight);
           return chatContentHeight;
        }
        anchors.left: (chatFlag==0)?parent.left:rect_myhead.right;
        anchors.leftMargin: (chatFlag==1)?4:(parent.width-width-60);
        anchors.top: imgTriangle.top;
        anchors.topMargin: 4;        
        border.width: 0
        border.color: (chatFlag == 1)?"gray":JSConst.chatitem_rect_green
        radius: 1
        color: (chatFlag == 1)? "white":JSConst.chatitem_rect_green
        TextWithImage {
            id: contents
            text: chatContents;
            color: "black"
            width: parent.width            
            wrapMode: Text.Wrap
            smooth: true            
            textFormat: (chathasEmoji==0)?Text.StyledText:Text.RichText;
            //textFormat: Text.StyledText;   //目前看这个类型显示比较好RichText对文字显示不够但是对html彩色字体显示好；
            renderType: Text.NativeRendering         
            visible:(chatDataType==wordsType)?true:false;
            font.pixelSize: 17
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignLeft
            clip:true;
        }   

        Rectangle {
            id: friendMessageVoice
            visible: chatDataType == voiceType ? true : false
            color: "transparent"
            radius: 3

            anchors {
                fill: rect_contents
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
                source: chatFlag === 1 ? "qrc:/img/sound/st_m_sound_1.png" : "qrc:/img/sound/st_m_sound_11.png"
                fillMode: Image.PreserveAspectFit
                mirror: chatFlag === 0 ? false : true
            }
            Image {
                id: voiceImage2
                height : 22
                width: 22
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                source: chatFlag === 0 ? "qrc:/img/sound/st_m_sound_2.png" : "qrc:/img/sound/st_m_sound_22.png"
                fillMode: Image.PreserveAspectFit
                mirror: chatFlag === 0 ? false : true
            }
            Image {
                id: voiceImage3
                height : 22
                width: 22
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                source: chatFlag === 0 ? "qrc:/img/sound/st_m_sound_3.png"  : "qrc:/img/sound/st_m_sound_33.png"
                fillMode: Image.PreserveAspectFit
                mirror: chatFlag === 0 ? false : true
            }

            Text {
                id: voicePlaySeconds;
                text: chatVoiceSeconds + "s"
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
                loops: chatVoiceSeconds + 1
            }

            Voice {id: playVoice;}

            /* 点击播放语音 */
            MouseArea {
                property int playSwitch: 0
                anchors.centerIn: parent
                anchors.fill: parent
                onClicked: {
                    if (playSwitch === 0) {
                        playVoice.playVoice(chatUid, chatMessageIndex);
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
        NormalPicture {id: displayPicture}
        /*  图片显示 */
        Image {
            id: friendMessagePicture
            visible: chatDataType == imageType ? true : false
            height: chatPictureHeight + 1
            width: chatPictureWidth + 1
            source: Qt.resolvedUrl(chatPicture)
            fillMode: Image.PreserveAspectFit

            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            /* 鼠标双击弹出大图 */
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    JSConst.showLogInfo("chatUid:",chatUid);
                    JSConst.showLogInfo("chatMessageIndex:",chatMessageIndex);
                    displayPicture.displayNormalPicture(chatUid, chatMessageIndex);
                }
            }
        }
        Component.onCompleted: {
            JSConst.showLog("parent width: "+width+" "+contents.paintedWidth);
        }


    }


    function testshemoji(str) {
       var vstr="";
       var str1="<img src=\"qrc:/img/emoji/"+"1f380.png\" source=\"qrc:/img/emoji/"+"1f380.png\" width=\"24\" height=\"24\" /> ";
       vstr=str1+str1+str1+str1+str1+str1+str1;
        console.log("test vstr_________________________:"+vstr)
       return vstr;
    }

    function getemoji(str){
      var s =EMOJIMAP.getEMOmap(str);
      var arrstr=str.split("@*@");
      return arrstr[0];
    }

    //测试添加图片是否能显示；
    function addtestimg(str){
        str=str+" <img src="+"\""+"qrc:/img/emoji/1f447.png"+"\" "+ "width=\"24\" height=\"24\"\" />";
        return str;
    }

}
