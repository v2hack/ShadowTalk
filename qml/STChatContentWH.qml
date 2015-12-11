/*******************************************************************
 *  Copyright(c) 2014-2015 PeerSafe
 *  All rights reserved.
 *
 *  文件名称: STChatContentWH.qml
 *  简要描述: 测试内容实际宽高
 *
 *  当前版本:1.1
 *  作者: 黄松发
 *  日期: 2015-12-5
 *  说明:
 ******************************************************************/
import QtQuick 2.5
import QtQuick.Controls 1.0;
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2;
import "js_st_const.js" as JSConst;

Rectangle {
    id:rect_main;
    width: 800
    height: 600
    color:"green";
    Rectangle{
        id:rect_conent;
        anchors.top: rect_main.top;
        width:200;
        height:50;
        anchors.left:parent.left
        anchors.leftMargin: parent.width-width-60
        anchors.topMargin: 4;
        border.width: 0
        border.color: "#bcbfc4";
        radius: 1
        color: "#b4eb7c" ;
    Text {
        id: contents
        text: "";
        color: "black"
        width: parent.width
        anchors.left: rect_conent.left;
        anchors.top:rect_conent.top;
        anchors.margins: 4;
        font.pixelSize: 17
        wrapMode: Text.WrapAnywhere
        lineHeight: 5+contents.font.pixelSize
        lineHeightMode: Text.FixedHeight
        textFormat: Text.RichText;
        font.wordSpacing: 1.0
        smooth: true
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    }
    //测试纵向(height)高度,当width>200;
    Rectangle{
        id:rect_texttxt;
        anchors.left: rect_main.left;
        anchors.top: rect_main.top;
        width: 200;
        height: 600;
        color:"#B0C4DE";
        clip:true;
        anchors.topMargin: 4;
    TextWithImage{
        id:testTxt;
        text: "";
        color: "black"
        anchors.left: rect_texttxt.left;
        anchors.top: rect_texttxt.top;
        anchors.margins: 4;
        font.pixelSize: 17
        anchors.fill: parent
        wrapMode: Text.Wrap
        textFormat : Text.RichText;
        font.pointSize: 10
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        clip:true;
     }
    }
    //横向(width)长度,当width<200
    Rectangle{
        id:rect_c1;
        anchors.left: rect_texttxt.right;
        anchors.top: rect_texttxt.top;
        width: 200;
        height: 600;
        color:"blue";
    TextWithImage{
        id:testfreewidth;
        text: "";
        color: "black"
        anchors.left: rect_texttxt.left;
        anchors.top: rect_texttxt.top;
        anchors.margins: 4;
        font.pixelSize: 17
        wrapMode: Text.PlainText;
        font.pointSize: 10
        verticalAlignment: Text.AlignLeft
        horizontalAlignment: Text.AlignLeft
     }
    }
    Rectangle{
        id:rect_bottom
        anchors.bottom: rect_main.bottom;
        height:50;
        width:parent.width;
        color:"#f0f0f0f0";
        Button{
            id :btn1;
          anchors.left: parent.left;
          anchors.leftMargin: 50;
          text:" show ";
          anchors.bottom: parent.bottom;
          anchors.bottomMargin: 10;
          onClicked: showall();
        }
        Button{
          anchors.left: btn1.left;
          anchors.leftMargin: btn1.width+ 50;
          text:" set Height ";
          anchors.bottom: parent.bottom;
          anchors.bottomMargin: 10;
          onClicked: setHeight();
        }
    }
    function addmsg(str){
        JSConst.showLog("testTxt content is :"+str);
        testTxt.text=str;
        testfreewidth.text=str;
        JSConst.showLog("testTxt contentwidth:"+testTxt.contentWidth);
        JSConst.showLog("testTxt width:"+testTxt.width);
        JSConst.showLog("testTxt contentheight:"+testTxt.contentHeight);
        JSConst.showLog("testTxt height:"+testTxt.height);

        JSConst.showLog("testfreewidth contentwidth:"+testfreewidth.contentWidth);
        JSConst.showLog("testfreewidth width:"+testfreewidth.width);
        JSConst.showLog("testfreewidth contentheight:"+testfreewidth.contentHeight);
        JSConst.showLog("testfreewidth height:"+testfreewidth.height);
    }
    function getWidth(){
        var w1=testTxt.contentWidth;
        var w2=testfreewidth.contentWidth;
        var w=w1+16;
        if (w1>w2){
            w=w2+8;
            //小192的宽度,做个补丁，由于字体和margin两边不一样造成小部分差异;
            if (w2>170)
            w=w+10;
        }
        return w;
    }
    function getHeight(){
        var w1=testTxt.contentWidth;
        var w2=testfreewidth.contentWidth;
        var h=28;
        if (w1<w2)
            h=testTxt.contentHeight;
        return h;
    }

    function setHeight()
    {
       testTxt.height=50;
       //rect_conent.height=rect_conent.height+60;
        rect_conent.height=testTxt.contentHeight+20;
        rect_conent.width=testTxt.contentWidth+20;
        contents.text="11"+str2;
    }

    function showall(){
        console.log("begin to show all_________");
        var str1="本书版权即将到期，准备续约中！期间如遇下架，敬请谅解。 十年前，顺子的父亲带领一批神秘人进入茫茫的大雪山，闯入凶险莫名的地宫墓室，发现了数不胜数的金银财宝，但他们非但不能带着这些财宝离开，反而被困此地，几乎全部死于非命。 　 十年后，“我们”和顺了一行人再次踏足云顶天宫，这更是一次直逼死亡的惊险大穿越：昆仑胎、墙串子、百足神龙等前所未见的怪异事物接替出现，藏尸阁、排道、火山口、门殿、殉葬渠等诡异恐怖之所带来超强的感官刺激"+"<img src=\"img/1F600.png\" width=\"20\" height=\"20\" align=\"bottom\">";
        var str2="<img src=\"img/1F600.png\" width=\"24\" height=\"24\" align=\"bottom\"> ";
        var str3="";
        var str4="1"
        str2=str2+str2+str2+str2+str2+str2+str2;
        testTxt.text=str2;
        console.log("testTxt contentwidth:"+testTxt.contentWidth);
        console.log("testTxt width:"+testTxt.width);
        console.log("testTxt contentheight:"+testTxt.contentHeight);
        console.log("testTxt height:"+testTxt.height);
        contents.text=str4;
        rect_conent.height=testTxt.contentHeight+20;
        rect_conent.width=testTxt.contentWidth+20;


        //contents.width=testTxt.contentWidth;
        //contents.height=testTxt.contentHeight;
        //contents.text=str2;
    }
}

