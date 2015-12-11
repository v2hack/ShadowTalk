import QtQuick 2.0

/* 语音显示 */
Rectangle {
    id: friendMessageVoice

    visible: dataType == voiceType ? true : false
    color: "transparent"
    radius: 3

    anchors {
        fill: parent
        left:parent.left
        leftMargin: 10
    }

    Image {
        id: voiceImage1
        height : 22
        width: 22
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        source: direct === 0 ? "qrc:/img/sound/st_m_sound_1.png" : "qrc:/img/sound/st_m_sound_11.png"
        fillMode: Image.PreserveAspectFit
        mirror: direct === 0 ? false : true
    }
    Image {
        id: voiceImage2
        height : 22
        width: 22
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        source: direct === 0 ? "qrc:/img/sound/st_m_sound_2.png" : "qrc:/img/sound/st_m_sound_22.png"
        fillMode: Image.PreserveAspectFit
        mirror: direct === 0 ? false : true
    }
    Image {
        id: voiceImage3
        height : 22
        width: 22
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        source: direct === 0 ? "qrc:/img/sound/st_m_sound_3.png"  : "qrc:/img/sound/st_m_sound_33.png"
        fillMode: Image.PreserveAspectFit
        mirror: direct === 0 ? false : true
    }

    Text {
        id: voicePlaySeconds;
        text: voiceSeconds + "s"
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 8
        }
        font.family: chineseFont.name;
    }

    /* 顺序播放 */
    SequentialAnimation {
        id: voiceAnim
        function stopVoiceAnim() {
            voiceAnim.stop();
            voiceImage1.opacity = 1;
            voiceImage2.opacity = 1;
            voiceImage3.opacity = 1;
        }

        NumberAnimation {
            target: voiceImage1
            property: "opacity"
            from: 1
            to: 0
            duration: 1
        }
        NumberAnimation {
            target: voiceImage2
            property: "opacity"
            from: 1
            to: 0
            duration: 1
        }
        NumberAnimation {
            target: voiceImage3
            property: "opacity"
            from: 1
            to: 0
            duration: 1
        }
        NumberAnimation {
            target: voiceImage1
            property: "opacity"
            from: 0
            to: 1.0
            duration: 120
        }
        NumberAnimation {
            target: voiceImage2
            property: "opacity"
            from: 0
            to: 1.0
            duration: 240
        }
        NumberAnimation {
            target: voiceImage3
            property: "opacity"
            from: 0
            to: 1.0
            duration: 360
        }
        PauseAnimation {
            duration: 200
        }
        loops: voiceSeconds + 1
    }

    /* 点击播放语音 */
    MouseArea {
        property int playSwitch: 0
        anchors.centerIn: parent
        anchors.fill: parent
        onClicked: {
            if (playSwitch === 0) {
                playVoice.playVoice(uid, messageIndex);
                playSwitch = 1;
                voiceAnim.start();
            } else {
                playVoice.stopVoice();
                playSwitch = 0;
                voiceAnim.stopVoiceAnim();
            }
        }
    }
    z:1000
}
