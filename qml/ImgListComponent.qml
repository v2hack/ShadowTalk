/**
 *  功能描述: 显示单个表情组件
 *   选中表情增加突出效果
 *  hsf 2015-11-22
 *  @return
 */

import QtQuick 2.0
import "js_st_emoji.js" as EMOJIMAP;

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
            console.log("col1 inex image source:"+im1.source.toString());
            var pngfile=im1.source.toString();        
            var str=chatTextEdit.text.toString();
            if (chatTextInput.msg==""){
                chatTextInput.msg=str;
            }
            var strmsg=chatTextInput.msg;
            var filename=pngfile.substring(15,pngfile.length-4);
            console.log("col1 index filename :"+filename)
            filename="U+"+filename.toUpperCase();
            filename=EMOJIMAP.getEMOContent(filename);
            chatTextInput.msg=strmsg+filename;
            chatTextEdit.text="";            
            chatTextEdit.append(str+" <img src=\""+pngfile+"\" width=\"20\" height=\"20\"> " );
        }
    }
}

