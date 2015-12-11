/*
 *  文件: js_st_const.js
 *  功能: qml公共变量模块
 *  作者: 黄松发
 *  时间: 2015-12-5 12:26:27
 */

var blueColorArr=[
            "#000079",
            "#000093",
            "#0000C6",
            "#0000C6",
            "#0000E3",
            "#4682B4",
            "#4A4AFF",
            "#6A6AFF",
            "#7D7DFF",
            "#9393FF",
            "#AAAAFF",
            "#B9B9FF",
            "#CECEFF"];

var greenColorArr =[
            "#467500",
            "#548C00",
            "#64A600",
            "#73BF00",
            "#82D900",
            "#8CEA00",
            "#9AFF02",
            "#A8FF24",
            "#b4eb7c",
            "#C2FF68",
            "#CCFF80",
            "#D3FF93",
            "#DEFFAC"
        ];

var chatitem_rect_green=greenColorArr[7];

//接收和发送头像的色彩 JsCommon.getColor(name) : "#508cc0";
var chatitem_rece_blue=blueColorArr[7];
var chatitem_send_blue="#508cc0";

var redColorArr=[
            "#000000",
            "#4D0000",
            "#600000",
            "#750000",
            "#930000",
            "#AE0000",
            "#CE0000",
            "#EA0000",
            "#FF0000",
            "#FF2D2D",
            "#FF5151",
            "#ff7575",
            "#FF9797"
        ]
var graycolorArr=[
            "gray",
            "#efefef"
           ]
var login_recct_loginQrWindow_color=graycolorArr[1];

var chatitem_myname="我";

//png图片
var chatinput_res_png_emoji= "qrc:/img/st_chat_expression.png";
var chatinput_res_png_emojiclose="qrc:/img/st_button_close_1.png";
var chatblank_res_png_imgcentin="qrc:/img/st_qr_process.png";
var main_res_png_title_logo="qrc:/img/st_title_logo.png";

var chatitem_res_png_right="qrc:/img/st_green_point.png";  //me
var chatitem_res_png_left="qrc:/img/st_white_point.png";

//字体资源
var chatinput_res_font_fangzheng="qrc:/res/fonts/fangzheng_gbk.ttf";

//main控制显示类型；
var main_itype_friendListselect=2;
var main_itype_blankselect     =0;
var main_itype_columnselect    =1;

//打印日志
var isdebug=true;
function showLog(str){
    if (isdebug)
    console.log(str);
}
function showLogInfo(strfun,log){
    if (isdebug)
    console.log(strfun+"-----------------------------------------------:"+log);
}

//以下变量是测试时使用
var Test_chatFlag_int=0;

function getTestChatFlag(){
   if (!isdebug) return;
   if (Test_chatFlag_int==0){
       Test_chatFlag_int=1;
   } else
   {
       Test_chatFlag_int=0;
   }
   return Test_chatFlag_int;
}




