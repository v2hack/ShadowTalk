/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: TextWithImage.qml
 *  简要描述: 显示聊天内容富文本框
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/

import QtQuick 2.0

Text {
    width: parent.width
    font.pointSize: 14
    wrapMode: Text.WordWrap
    textFormat: Text.StyledText
    horizontalAlignment: friendItemIcon.hAlign
}
