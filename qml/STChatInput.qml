/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatTextInput.qml
 *  简要描述: 聊天输入框
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015/07/20，2015-12-5
 *  说明:
 ******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.2
import "js_st_const.js" as JSConst;
import "js_st_emoji.js" as JSEmoji;

import st.info.MessageManager 1.0

Rectangle {
    id: chatTextInput
    z:400

    property int friendIndex: 0
    property int hasEMOJI: 0;
    property string msg: "";
    property string souTextOld: "";
    property string souTextNew: "";

    /* 输入工具栏 */
    Rectangle {
        id: chatTool
        width: parent.width;
        height: 1;
        opacity: 0.3
        color: "#efefef"
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
            if (chatedit.text != "") {
                JSConst.showLog("chatedit.text :--------------"+chatedit.text.toString());
                getChatContent(chatedit.text.toString());
                //如果为null,没空格输入等，不能发送；
                if (souTextOld==="ent:0; text-indent:0px;\"><br />") {
                    return;
                }

                var unicodestr=JSEmoji.getEMOContentReExp(souTextOld);
                cppSendMessage.sendMessage(unicodestr);
                chatedit.text = "";
                msg="";
                souTextOld="";
                souTextNew=""; //暂时不用
            }
        }
    }


    /* description: 从TextArea中提前文本内容;
     *              此方法有待于再改进2015年12月5日
     * author:      hsf
     * date:        2015-12-5
     */
    function getChatContent(text){        
        var txt=text;
        var fromstr1=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;"+
                    "-qt-block-indent:0; text-indent:0px;";
        JSConst.showLog("chat souText ++++++++++++++++++"+fromstr1.length);
        var fromstr="<p style="
        var endstr="</p></body></html>";
        var ifrom=txt.indexOf(fromstr);
        var iend=txt.indexOf(endstr);
        var stxt=txt.substring(ifrom+fromstr1.length+13,iend);
        souTextOld=stxt;
        return souTextOld;
    }
    function getsourceContent(text){
        chatedit.textFormat=Text.AutoText;
        souTextOld=chatedit.text.valueOf();
        JSConst.showLog("getsourceContent AutoText++++++______+++valueOf:"+souTextOld);
        JSConst.showLog("getsourceContent AutoText++++++______+++valueOf:"+chatedit.text.toString());
        chatedit.textFormat=Text.PlainText;
        souTextOld=chatedit.text.valueOf();
        JSConst.showLog("getsourceContent PlainText++++++______+++valueOf:"+souTextOld);
        JSConst.showLog("getsourceContent PlainText++++++______+++valueOf:"+chatedit.text.toString());
        chatedit.textFormat=Text.StyledText;
        souTextOld=chatedit.text.valueOf();
        JSConst.showLog("getsourceContent StyledText++++++______+++valueOf:"+souTextOld);
        JSConst.showLog("getsourceContent StyledText++++++______+++valueOf:"+chatedit.text.toString());
        chatedit.textFormat=Text.RichText;
        return souTextOld;
    }

    //显示表情；
    function setEmojiShow(canShow){
        rect_emojiview.visible=canShow;
    }

    function setEmojiVisible(){
        if (rect_emojiview.visible){
            rect_emojiview.visible=false;
        } else
        {
            rect_emojiview.visible=true;
        }
    }
    /* 发送图片和发送表情 */
    Rectangle {
        id: chatPictureButton;
        width: parent.width;
        height: 28;
        color: "#efefef"
        anchors {
            top: chatTool.bottom;
        }

        Image {
            id: sendPictureImage;
            height : 22
            width: 22
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 10
            }
            source: JSConst.chatinput_res_png_emoji;
            fillMode: Image.PreserveAspectFit
        }
        MouseArea {
            id:mouse_showEmoji;
            anchors.fill: sendPictureImage;
            onClicked: {
                JSConst.showLog("c++ begin to show emoji ........");
                setEmojiVisible();
                if (hasEMOJI==0){
                    rect_emojiview.getAllEmoji();
                    hasEMOJI=1;
                }
            }
        }
        //显示选择表情列表qml add by hsf 2015年11月27日
        Rectangle{
             id: rect_emojiview
             width: 420
             height: 150
             anchors.bottom: chatPictureButton.top;
             anchors.left: chatPictureButton.left;
             anchors.leftMargin: 10;
             visible: false;
             z:1000;             
             function getAllEmoji(){
                 list1.loademo(1);
                 list2.loademo(2);
                 list3.loademo(3);
                 list4.loademo(4);
             }
             Rectangle {
                 id: emojiList;
                 anchors {
                     top:parent.top
                     left:parent.left
                 }
                 clip: true
                 width:420
                 height:150
                 // 可视元素模型（直接输出可视元素）
                 VisualItemModel {
                     id: pageModel
                     Rectangle{
                         width:rect_emojiview.width;
                         height:30;
                         color: "#f0f0f0"
                         STChatEmojiView{
                             id:list1;
                         }
                     }
                     Rectangle{
                         width:rect_emojiview.width;
                         height:30;
                         color: "#f0f0f0"
                         STChatEmojiView{
                             id:list2;
                         }
                     }
                     Rectangle{
                         width:rect_emojiview.width;
                         height:30;
                         color: "#f0f0f0"
                         STChatEmojiView{
                             id:list3;
                         }
                     }
                     Rectangle{
                         width:rect_emojiview.width;
                         height:30;
                         color: "blue"
                         STChatEmojiView{
                             id:list4;
                         }
                     }
                 }

                 ListView{
                     id: listview_emoji
                     model: pageModel
                     anchors.fill: parent
                     orientation: ListView.Horizontal
                     snapMode: ListView.SnapOneItem
                     highlightRangeMode: ListView.StrictlyEnforceRange
                     cacheBuffer: 0  // 缓存区域高度、宽度、元素个数？
                     displayMarginBeginning:0
                     displayMarginEnd:0

                     clip: true
                 }
             }

             Row {
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.bottom: parent.bottom
                 anchors.bottomMargin: 5
                 z: 2
                 spacing: 20

                 Repeater {
                     opacity: 0.8
                     model: listview_emoji.model.count
                     Rectangle {
                         width: 10;
                         height: 10
                         radius: 5
                         color: listview_emoji.currentIndex == index ? "#ff5656" : "#b2b2b2"
                         MouseArea {
                             width: 20; height: 20
                             anchors.centerIn: parent
                             onClicked: listview_emoji.currentIndex = index
                         }
                     }
                 }
             }

             Image {
                 id:img_emojiexit;
                 anchors.right:rect_emojiview.right;
                 anchors.rightMargin: 20;
                 anchors.bottom: rect_emojiview.bottom;
                 width: 15;
                 height:15;
                 source:JSConst.chatinput_res_png_emojiclose;
                 MouseArea{
                     id:mouse_exit;
                     anchors.fill: img_emojiexit;
                     onClicked: setEmojiVisible();
                 }
             }


         }


        Image {
            id: sendPictureFile;
            height : 22
            width: 22
            anchors {
                verticalCenter: parent.verticalCenter
                left: sendPictureImage.right
                leftMargin: 10
            }
            source: "qrc:/img/st_chat_delivery.png";
            fillMode: Image.PreserveAspectFit

        }
        MouseArea {

        }
    }



    /* 聊天内容发送框 */
    Rectangle {
        id: chatTextEditRectangle;
        width: parent.width;
        height: parent.height - chatTool.height - 35 - 28;
        color: "#efefef"
        anchors {
            top: chatPictureButton.bottom;
        }

        /* 输入编辑栏 */
        TextEdit {
            id: chatedit;
            anchors.fill: chatTextEditRectangle;
            wrapMode: TextEdit.WrapAnywhere
            selectByMouse: true
            //backgroundVisible: false
            //frameVisible: false
            font.family: chineseFont.name;
            textFormat: Text.RichText
            focus: true;
            Keys.onReturnPressed: {
              JSConst.showLog("input  return keys ..............");
            }
        }
        Text{
            id:chatetext;

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
                    source:JSConst.chatinput_res_font_fangzheng;
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
                /*
                onClicked: {
                    messageColumn.addTestContent(getChatContent(chatedit.text.toString()));
                    JSConst.showLog("emoji unicode .....+++++++++++++++++++"+JSEmoji.getEMOContentReExp(souTextOld));
                    //cppSendMessage.sendMessage(getChatContent(chatedit.text.toString()));
                    chatedit.text="";
                    msg="";
                    souTextOld="";
                    souTextNew="";
                }
                */
            }
        }
    }
}

