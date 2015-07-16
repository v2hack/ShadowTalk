import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0


Rectangle {
    id: baseWindows;
    width: Math.round(890)
    height: Math.round(640)
    radius: 5;
    color: "transparent"

    /* 主窗口可见 */
    visible: true
    /* 透明度 */
    opacity: 0.97

    /* 主窗口鼠标拖拽 */
    MouseArea {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "0,0"

        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            /* 鼠标偏移量 */
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            /* 如果mainwindow继承自QWidget,用setPos */
            mainwindow.setX(mainwindow.x + delta.x)
            mainwindow.setY(mainwindow.y + delta.y)
        }
    }

    /* 添加关闭按钮 */
    Rectangle{

        id:closeBtn
        height: 25
        width: 25
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        color:"#000000"
        z: 100

        Text{
            text:"x"
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //Qt.quit()无法关闭窗口
                mainwindow.close()
            }
        }
    }

    Rectangle {
        id: firstLayerWindows
        width: Math.round(baseWindows.width - 2)
        height: Math.round(baseWindows.height - 2)
        anchors.centerIn: parent
        radius: 5
        border.color: "#a0a0a4"
        border.width: 2

        Rectangle {
            id: secondLayerWindows
            width: Math.round(firstLayerWindows.width - 2)
            height: Math.round(firstLayerWindows.height - 2)
            smooth: true
            radius: 5
            anchors.left: parent.left;
            anchors.leftMargin: 1
            anchors.top: parent.top;
            anchors.topMargin: 1

            /* 背景 */
            Component {
                id: backGroundComponent;
                Rectangle {
                    id: backGroundRectangle
                    width: Math.round(secondLayerWindows.width/3 - 4);
                    height: Math.round(secondLayerWindows.height - 4);
                    color: "#000000"
                    radius: 5
                }
            }

            /* 搜索组件 */
            Component {
                id: searchComponent;
                Rectangle {
                    id:searchRectangle
                    width: Math.round(200)
                    height: Math.round(20)
                    radius: 5
                    border.color: "#a0a0a4"
                    color: "#808080"
                }
            }

            /* 友好及联系人组件 */
            Component {
                id: listComponent;

                Flipable {
                    id: flipable
                    width: secondLayerWindows.width/3 - 4
                    height: 30

                    property bool flipped: false

                    front: Rectangle {
                        Rectangle {
                            id: titleFront
                            width: secondLayerWindows.width/3 - 4
                            height: 30
                            color: "#33ccbf"
                        }
                        Rectangle {
                            id: friendList
                            anchors.top: titleFront.bottom;
                            width: secondLayerWindows.width/3 - 4
                            height: 512
                            color: "#2c2c2c"
                            opacity: 0.8
                        }
                    }

                    back: Rectangle {
                        Rectangle {
                            id: titleBack
                            width: secondLayerWindows.width/3 - 4
                            height: 30
                            color: "#33ccbf"
                        }
                        Rectangle {
                            id: contactList
                            anchors.top: titleBack.bottom;
                            width: secondLayerWindows.width/3 - 4
                            height: 512
                            color: "#2c2c2c"
                            opacity: 0.8
                        }
                    }

                    transform: Rotation {
                        id: rotation
                        origin.x: flipable.width/2
                        origin.y: flipable.height/2
                        axis.x: 0;
                        axis.y: 1;
                        axis.z: 0;
                        angle: 1;    // the default angle
                    }

                    states: State {
                        name: "back"
                        PropertyChanges {
                            target: rotation;
                            angle: 180;
                        }
                        when: flipable.flipped
                    }

                    transitions: Transition {
                        NumberAnimation {
                            target: rotation;
                            property: "angle";
                            duration: 200;
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: flipable.flipped = !flipable.flipped
                    }
                }
            }

            /* 低端设置组件 */
            Component {
                id: bottomSettingComponent;
                Rectangle {
                    id: bottomSettingComponentRectangle;
                    width: Math.round(secondLayerWindows.width/3 - 4);
                    height: Math.round(52);
                    radius: 5;
                    color: "#515050"

                    /* 退出按钮 */
                    Button {
                        id: exitButton;
                        text: "";
                        width: 25;
                        height: 30;
                        Image {
                            id: exitButtonImage;
                            width: parent.width;
                            height: parent.height;
                            source: "qrc:/img/st_setting_exit.png";
                            fillMode: Image.PreserveAspectFit
                        }
                        style: ButtonStyle {
                            background: Rectangle {
                                opacity: 0
                            }
                        }

                        anchors.left: parent.left;
                        anchors.leftMargin: parent.width/4 - 16;
                        anchors.top: parent.top;
                        anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;
                    }


                    /* 声音按钮 */
                    Button {
                        id: soundButton;
                        width: 35;
                        height: 30;
                        Image {
                            width: parent.width;
                            height: parent.height;
                            source: "qrc:/img/st_setting_sound.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        style: ButtonStyle {
                            background: Rectangle {
                                opacity: 0
                            }
                        }
                        anchors.left: parent.left;
                        anchors.leftMargin: parent.width/2 - 16;
                        anchors.top: parent.top;
                        anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;
                    }

                    /* 锁屏按钮 */
                    Button {
                        id: lockScreenButton;
                        width: 38;
                        height: 33;

                        style: ButtonStyle {
                            background: Rectangle {
                                opacity: 0
                            }
                        }
                        Image {
                            width: parent.width;
                            height: parent.height;
                            source: "qrc:/img/st_setting_lock_screen.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        anchors.left: parent.left;
                        anchors.leftMargin: parent.width/4*3 - 16;
                        anchors.top: parent.top;
                        anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;
                    }
                }
            }

            /* 导入背景 */
            Loader {
                id: backGroundLoader;
                anchors.top: parent.top;
                anchors.topMargin: 2
                anchors.left: parent.left;
                anchors.leftMargin: 2;
                sourceComponent: backGroundComponent;
            }

            /* 导入搜索栏 */
            Loader {
                id: searchLoader;
                anchors.top: parent.top;
                anchors.topMargin: 8
                anchors.left: backGroundLoader.left
                anchors.leftMargin: (secondLayerWindows.width/3 - 4)/2 - 100;
                sourceComponent: searchComponent;
            }

            Loader {
                id: listLoader;
                anchors.top: searchLoader.bottom;
                anchors.topMargin: 6;
                anchors.left: backGroundLoader.left
                sourceComponent: listComponent;
            }

            Loader {
                id: bottomSettingLoader;
                anchors.bottom: backGroundLoader.bottom;
                anchors.topMargin: 515;
                anchors.left: backGroundLoader.left
                sourceComponent: bottomSettingComponent;
            }
        }
    }
}
