/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: LoginProcess.qml
 *  简要描述: 登陆进度组件
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.2

/* 画原型进度 */
Rectangle {
    id: loginProcess
    property int gValue: 0
    property int colorFlag: 0
    color: "#efefef"

    function rePaint() {
        loginCanvas.requestPaint();
    }

    Canvas {
        id: loginCanvas
        width: 640
        height: 480
        contextType: "2d"

        anchors {
            top: parent.top
            topMargin: 20
        }

        onPaint: {
            /* 描边 */
            context.strokeStyle = (colorFlag == 0 ? "#00b9fe" : "#ccc6bf");
            /* 图形内部色彩 */
            context.fillStyle = (colorFlag == 0 ? "#00b9fe" : "#ccc6bf");
            /* 描边线粗度 */
            context.lineWidth = 1;
            context.beginPath();
            context.moveTo(160, 160);//start point
            var du =  3.1414927 * 2 /360 ;
            /* arc(横坐标，纵坐标，半径，起始点度数， 结束点度数， 顺时针（逆时针）)*/
            context.arc(160, 160, 140, -Math.PI/2,  -Math.PI/2 + gValue * du, 0)
            context.fill();
            context.stroke();
        }
    }
}

