/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatBlank.qml
 *  简要描述: 空白页
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-8
 *  说明:
 ******************************************************************/

import QtQuick 2.0
import "js_st_const.js" as JSConst;

Item {
    id: item_chatblank;
    clip:true;

    Rectangle{
        id:rect_chatblank
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10;
        color:"#f0f0f0"
        height: parent.height
        border.width: 0
        border.color: "#f0f0f0"
        radius: 0

        Rectangle{
            id:rect_chatblank_image
            anchors.centerIn: parent;

            Image{
               id:img_chatblank
               source:JSConst.chatblank_res_png_imgcentin;
               fillMode: Image.PreserveAspectFit
               visible:false;
            }

        }

    }

}
