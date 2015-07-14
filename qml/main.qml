import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3

ApplicationWindow {

    title: qsTr("Hello World")
    width: 850
    height: 600
    visible: true
    opacity: 1

    // 背景图片
    style: ApplicationWindowStyle {
        background: BorderImage {
            source: "qrc:/img/st_left_background.png"
            border { left: 20; top: 20; right: 20; bottom: 20 }
        }
    }


    Rectangle {
        id: root;





    }


}
