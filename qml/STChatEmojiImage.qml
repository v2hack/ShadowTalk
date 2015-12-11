/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatEmojiImage.qml
 *  简要描述: 显示单个表情
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/

import QtQuick 2.0
import "js_st_emoji.js" as EMOJIMAP;
import "js_st_const.js" as JSConst;

Rectangle{
    id:imgListComponent;
    width: 30;
    height: 30;
    property string imgsource: "";
    color: backmouse.pressed ? "#a6a6a6" : "transparent"
    Image{
        id:im1;
        source:imgsource;
        width:20;
        height: 20;
        anchors.centerIn: parent;
        antialiasing:true;
    }
    MouseArea {
        id: backmouse
        hoverEnabled: true
        anchors.fill: parent//相对于矩形图片区域描点
        anchors.margins: -10//边距
        onEntered:{
            imgListComponent.color="#fcfcfc";
        }
        onExited:{
            imgListComponent.color="transparent";
        }
        onClicked: {

            JSConst.showLog("col1 inex image source:"+im1.source.toString());
            var pngfile=im1.source.toString();
            var str=chatedit.text.toString();
            var strmsg=chatTextInput.msg;
            var filename=pngfile.substring(15,pngfile.length-4);

            JSConst.showLog("col1 index filename :"+filename)

            filename="U@"+filename.toUpperCase();
            var emojiUnicode=EMOJIMAP.getEMOContent(filename);

            JSConst.showLog("c++ emoji char:"+emojiUnicode);
            chatTextInput.msg=strmsg+emojiUnicode;
            chatedit.text=str+"<img src=\""+pngfile+"\" width=\"24\" height=\"24\">" ;
            chatedit.cursorPosition=chatedit.text.length;
        }
    }
}

