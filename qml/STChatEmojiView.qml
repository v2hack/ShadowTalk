/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatEmojiView.qml
 *  简要描述: 显示表情列表,有空可以改成Grid显示更友好
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.1;
import "js_st_showemoji.js" as Showemoji;

Rectangle{
    id:rect_emojilist;
    width: 210;
    height: 160;

    function loademo(p){
        listimg1.loademoji(p);
    }
    ListView {
        id : listimg1;
        anchors.fill: parent;
        model: imgEmojiModel1;
        delegate: imgDelegate;
        function loademoji(pages) {
            var data=Showemoji.getEmojiModel(pages);
            var jsonData=eval(data);
            model.append(jsonData);
        }

    }
    ListModel {
        id:imgEmojiModel1;
    }
    Component {
        id: imgDelegate
        Item
        {
            id:wrapper;
            width: 210;
            height: 30;

            RowLayout{
                id: banner
                width: 210;
                height: 30;
                anchors.fill: parent
                STChatEmojiImage{
                    imgsource: imgc1;

                }
                STChatEmojiImage{
                    imgsource: imgc2;

                }
                STChatEmojiImage{
                    imgsource: imgc3;

                }
                STChatEmojiImage{
                    imgsource: imgc4;

                }
                STChatEmojiImage{
                    imgsource: imgc5;

                }
                STChatEmojiImage{
                    imgsource: imgc6;

                }
                STChatEmojiImage{
                    imgsource: imgc7;

                }
                STChatEmojiImage{
                    imgsource: imgc8;

                }
                STChatEmojiImage{
                    imgsource: imgc9;

                }
                STChatEmojiImage{
                    imgsource: imgc10;

                }
                STChatEmojiImage{
                    imgsource: imgc11;

                }
                STChatEmojiImage{
                    imgsource: imgc12;

                }
            }
        }

    }
}



