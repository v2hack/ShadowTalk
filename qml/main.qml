import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3

ApplicationWindow {

    title: qsTr("ShadowTalk")
    visible: true
    opacity: 0.98
    Rectangle {
        width: 850
        height: 600

        /* 背景 */
        Component {
            id: backGroundComponent;
            Rectangle {
                Image {
                    source:  "qrc:/img/st_left_background.png";
                    fillMode: Image.PreserveAspectCrop;
                    width: 300;
                    height: 600;
                }
            }
        }

        /* 搜索组件 */
        Component {
            id: searchComponent;
            Rectangle {
                Image {
                    source:  "qrc:/img/st_top_search_area.png";
                    width: 180;
                    height: 24;
                }
            }
        }


        /* 好友列表组件 */
        Component {
            id: friendListComponent;
            Rectangle {
                Image {
                    id: st_friend_list_png;
                    source:  "qrc:/img/st_friend_list.png";
                    width: 300;
                    height: 28;
                }
            }
        }

        /* 联系人组件 */
        Component {
            id: contactListComponent;
            Rectangle {
                Image {
                    id: st_friend_list_png;
                    source:  "qrc:/img/st_friend_list.png";
                    width: 300;
                    height: 28;
                }
            }
        }

        /* 低端设置组件 */
        Component {
            id: bottomSettingComponent;
            Rectangle {
                id: bottomSettingComponentRectangle;
                width: 300;
                height: 50;

                Image {
                    id: bottomBackGroundImg;
                    width: parent.width;
                    height: parent.height;
                    source:  "qrc:/img/st_bottom_background.png";
                    fillMode: Image.PreserveAspectCrop;
                }

                /* 退出按钮 */
                Button {
                    id: exitButton;
                    text: "";
                    width: 25;
                    height: 30;
                    Image {
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
                    anchors.topMargin: bottomSettingComponentRectangle.height/2 - height/2;                }

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

        Loader {
            id: backGroundLoader;
            sourceComponent: backGroundComponent;
        }

        Loader {
            id: searchLoader;
            anchors.bottom: backGroundLoader.top;
            anchors.bottomMargin: 14
            anchors.left: parent.left;
            anchors.leftMargin: 60;
            anchors.top: parent.top;
            anchors.topMargin: 14
            sourceComponent: searchComponent;
        }

        Loader {
            id: friendListLoader;
            anchors.top: backGroundLoader.top;
            anchors.topMargin: 60;
            sourceComponent: friendListComponent;
        }

        Loader {
            id: contactListLoader;
            anchors.top: backGroundLoader.top;
            anchors.topMargin: 89;
            sourceComponent: contactListComponent;
        }

        Loader {
            id: bottomSettingLoader;
            anchors.bottom: parent.bottom;
            sourceComponent: bottomSettingComponent;
        }

    }
}
