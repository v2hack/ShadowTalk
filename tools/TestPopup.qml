import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0

/**
测试自定义弹出层：popup和mask
    /可设置动画类型
    /可设置是否显示遮罩
    用list替代combobox
*/
Item{
    width: 640
    height: 480

    // 定义鼠标可拖动区域
    MouseArea {
        anchors.fill: parent
        drag.target: popup;
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 30
        drag.maximumX: 150
        drag.filterChildren: true
        clip: true
    }

    // 弹出层
    Popup {
        id: popup
        width: 200; height: 300
        x: 200; y:100
        //anchors.centerIn: parent  // 注意：使用位移动画不能用anchors定位方式
        z: 101
        opacity: 0.8
        visible: false;
        radius: 5

        //
        Text{
            text: 'this is popop'
            anchors.bottom: parent.bottom
            anchors.centerIn: parent
        }
        Button {
            id: btnClose
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            text:"Close"
            width: 98
            onClicked: parent.hide()
        }
    }

    // 控制区
    Rectangle{
        width:300; height:300
        anchors.centerIn: parent
        Column{
            anchors.fill: parent
            spacing:10
            ComboBox {
                id: cmbAnimation
                width:300
                editable: true
                model: ["fade", "width", "height", "size", "flyDown", "flyUp", "flyLeft", "flyRight"]
            }
            ListView {
                visible: false
                id: lvAnimation
                width:300
                height: 200
                model: ["fade", "width", "height", "size", "flyDown", "flyUp", "flyLeft", "flyRight"]
            }
            CheckBox{
                id: chk
                text: 'show mask'
                checked: true
            }
            Button {
                id: btnPopup
                text: '显示自定义popup'
                onClicked:{
                    popup.showMask = chk.checked;
                    popup.animationType = cmbAnimation.currentText;
                    //popup.duration = 1000;
                    //popup.easingType = Easing.OutElastic;
                    popup.show();
                }
            }
        }
    }
}


