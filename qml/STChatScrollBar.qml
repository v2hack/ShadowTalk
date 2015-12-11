/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatScrollBar.qml
 *  简要描述: 通用的滚动条
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/
import QtQuick 2.0

Item {
    id: scrollBar
    property real position
    property real pageSize
    property variant orientation : Qt.Vertical
    property string scrollColor: "black"


    Rectangle {
        id: background
        anchors.fill: parent
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "white"
        opacity: 0.3
    }

    Rectangle {
        x: orientation == Qt.Vertical ? 1 : (scrollBar.position * (scrollBar.width-2) + 1)
        y: orientation == Qt.Vertical ? (scrollBar.position * (scrollBar.height-2) + 1) : 1
        width: orientation == Qt.Vertical ? (parent.width-2) : (scrollBar.pageSize * (scrollBar.width-2))
        height: orientation == Qt.Vertical ? (scrollBar.pageSize * (scrollBar.height-2)) : (parent.height-2)
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: scrollColor
        opacity: 0.7
    }
}
