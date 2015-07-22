import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0

// 页面
Rectangle {
    id: page
    width: 360
    height: 640
 
    // 模型
    ListModel {
        id: model
        ListElement { title: "1" }
        ListElement { title: "2" }
        ListElement { title: "3" }
        ListElement { title: "4" }
        ListElement { title: "5" }
        ListElement { title: "6" }
        ListElement { title: "7" }
        ListElement { title: "8" }
    }
 
    // 视图
    ListView {
        id: view
        anchors.fill: parent
        anchors.rightMargin: 12
        model: model
        delegate: delegate
        spacing: 5
    }
 
    // 代理
    Component {
        id: delegate
 
        // 列表项
        Rectangle {
            width: parent.width
            height: 100
            border.color: "red"
 
            Text {
                anchors.centerIn: parent
                text: title
                font.pointSize: 24
                color: "black"
            }
        }
    }
 
    // 滚动条
    Rectangle {
        id: scrollbar
        x: 350
        y: 0
        width: 10
        height: 640
        color: "black"
 
        // 按钮
        Rectangle {
            id: button
            x: 0
            y: view.visibleArea.yPosition * scrollbar.height
            width: 10
            height: view.visibleArea.heightRatio * scrollbar.height;
            color: "green"
 
            // 鼠标区域
            MouseArea {
                id: mouseArea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height - button.height
 
                // 拖动
                onMouseYChanged: {
                    view.contentY = button.y / scrollbar.height * view.contentHeight
                }
            }
        }
    }
}