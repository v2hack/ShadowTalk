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

    Rectangle {

        Image {
            id: st_backeground_png
            source:  "qrc:/img/st_left_background.png"
            fillMode: Image.PreserveAspectCrop
            width: 300
            height: 600
        }

        Image {
            id: st_bottom_backeground_png
            anchors.bottom: st_backeground_png.bottom;
            source:  "qrc:/img/st_bottom_background.png"
            fillMode: Image.PreserveAspectCrop
            width: 300
            height: 50
        }

        Image {
            id: st_friend_list_png
            anchors.top: st_backeground_png.top;
            anchors.topMargin: 60;
            source:  "qrc:/img/st_friend_list.png"
            width: 300
            height: 50
        }


        Image {
            id: st_top_search_png
            anchors.bottom: st_friend_list_png.top;
            anchors.left: st_backeground_png.left;
            anchors.verticalCenter: st_friend_list_png.Center;
            source:  "qrc:/img/st_top_search_area.png"
            width: 180
            height: 25
        }

    }
}
