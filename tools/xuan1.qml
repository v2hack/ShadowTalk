import QtQuick 2.0  
import QtQuick.Particles 2.0   
  
Rectangle {                                           // ���θ�Ԫ��  
  
    id: root  
  
    height: 540  
    width: 360  
  
    gradient: Gradient {                              // ���뽥��Ч��  
        GradientStop { position: 0; color: "#000020" }  
        GradientStop { position: 1; color: "#000000" }  
    }  
  
    MouseArea {                                       // Ϊ��ʵ�ֵ��Ч������  
        id: mouseArea  
        anchors.fill: root  
    }  
  
    ParticleSystem { id: sys1 }                         // ����ParticleSystem��������Ч  
    ImageParticle {                                     // Ҳ������ϵͳ�Ļ���Ԫ��  
        system: sys1                                    // ָ��ϵͳ  
        source: "qrc:///particleresources/glowdot.png"  // ����ѡ����"���"���ӣ���ϸ���ݼ��·��ڣ�1����  
        color: "cyan"                                   // ��ɫ  
        alpha: 0                                        // ͸����  
        SequentialAnimation on color {                  // ����ɫ�ϼ��붯��  
            loops: Animation.Infinite                   // ����ѭ������ͬ-1���������ֵ��ѭ���������  
            ColorAnimation {                            // ��ɫ����  
                from: "cyan"  
                to: "magenta"  
                duration: 1000  
            }  
            ColorAnimation {  
                from: "magenta"  
                to: "blue"  
                duration: 2000  
            }  
            ColorAnimation {  
                from: "blue"  
                to: "violet"  
                duration: 2000  
            }  
            ColorAnimation {  
                from: "violet"  
                to: "cyan"  
                duration: 2000  
            }  
        }  
        colorVariation: 0.3                             // ��ɫ�仯�ʣ���0��1��Խ������Ⱥ��ɫ��Խ�ḻ  
    }  
    //! [0]  
    Emitter {                                                  // ��������ǵķ�������  
        id: trailsNormal  
        system: sys1                                           // һ��Ҫָ�����������ϵͳ  
  
        emitRate: 500                                          // ÿ�����ӷ�����  
        lifeSpan: 2000                                         // ������������(����)  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle.cy       // ���䵽������ֵ  
        x: mouseArea.pressed ? mouseArea.mouseX : circle.cx       // ����ʹ��mouseArea����Ƿ��£�����ʹ�ð��µ����꣬����ʹ������ļ������ꡣ���������֮�����ܹ������ķ��䣬��Ե������QML�����԰󶨣������������ֵ�ĳ����仯��������������������Ӷ�����  
  
  
        velocity: PointDirection {xVariation: 4; yVariation: 4;}  // �����Ӳ���������ɢ��Ϊ��x,y�����ϵ��ٶ�  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;} // ��ɢ��Ϊ�ļ��ٶ�  
        velocityFromMovement: 8                                   // ���ڵ�ǰ���ӵ��˶�Ϊ�����һ��������ٶ�����  
  
        size: 8                                                   // ���Ӵ�С����λ�����أ�Ĭ��Ϊ16  
        sizeVariation: 4                                          // һ��������ӵ�size��endSize�ϵ�����  
    }  
    //! [0]                                                        
    ParticleSystem { id: sys2 }                                   // �ڶ�������ϵͳ����ǰ�ߴ�ͬС��  
    ImageParticle {  
        color: "cyan"  
        system: sys2  
        alpha: 0  
        SequentialAnimation on color {  
            loops: Animation.Infinite  
            ColorAnimation {                                       
                from: "magenta"  
                to: "cyan"  
                duration: 1000  
            }  
            ColorAnimation {  
                from: "cyan"  
                to: "magenta"  
                duration: 2000  
            }  
        }  
        colorVariation: 0.5  
        source: "qrc:///particleresources/star.png"               // ����ѡȡ��һ�ֲ�ͬ�����ӣ�star��С�����Ҿ������������ĶԽ���  
    }  
    Emitter {  
        id: trailsStars  
        system: sys2  
  
        emitRate: 100                                            // ���ٵ����ǲ����ڹ���У��ﵽѤ����Ч��  
        lifeSpan: 2200  
  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle.cy  
        x: mouseArea.pressed ? mouseArea.mouseX : circle.cx  
  
        velocity: PointDirection {xVariation: 4; yVariation: 4;}  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;}  
        velocityFromMovement: 8  
  
        size: 22  
        sizeVariation: 4  
    }  
    ParticleSystem { id: sys3; }                                // �����˶�������  
    ImageParticle {  
        source: "qrc:///particleresources/glowdot.png"  
        system: sys3  
        color: "orange"                                       
        alpha: 0  
        SequentialAnimation on color {                         // ��ʼֵΪ��ɫ������ɫ���������ں��̼��л�����Ϊ��ɫ�������ɫ  
            loops: Animation.Infinite  
            ColorAnimation {  
                from: "red"  
                to: "green"  
                duration: 2000  
            }  
            ColorAnimation {  
                from: "green"  
                to: "red"  
                duration: 2000  
            }  
        }  
  
        colorVariation: 0.2                                 // ������ֵ��1���Ϳ����������Ķ���Ч���ˣ����Ϊ0������Ⱥ����ɫ�Եõ���  
  
    }  
    Emitter {  
        id: trailsNormal2  
        system: sys3  
  
        emitRate: 300  
        lifeSpan: 2000  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle2.cy  
        x: mouseArea.pressed ? mouseArea.mouseX : circle2.cx  
  
        velocityFromMovement: 16  
  
        velocity: PointDirection {xVariation: 4; yVariation: 4;}  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;}  
  
        size: 12  
        sizeVariation: 4  
    }  
    ParticleSystem { id: sys4; }  
    ImageParticle {  
        system: sys4  
        source: "qrc:///particleresources/star.png"  
        color: "green"  
        alpha: 0  
        SequentialAnimation on color {  
            loops: Animation.Infinite  
            ColorAnimation {  
                from: "green"  
                to: "red"  
                duration: 2000  
            }  
            ColorAnimation {  
                from: "red"  
                to: "green"  
                duration: 2000  
            }  
        }  
  
        colorVariation: 0.5  
    }  
    Emitter {  
        id: trailsStars2  
        system: sys4  
  
        emitRate: 50  
        lifeSpan: 2200  
  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle2.cy  
        x: mouseArea.pressed ? mouseArea.mouseX : circle2.cx  
  
        velocityFromMovement: 16  
        velocity: PointDirection {xVariation: 2; yVariation: 2;}  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;}  
  
        size: 22  
        sizeVariation: 4  
    }  
  
  
  
    color: "white"                                                     // ���������color�����壬��Ϊ���ε���ɫ�ڽ��������Ѿ���ȷ����  
  
    Item {                                                             // ���ǿ���ʹ��Item������һ���߼����󣬲�Ϊ�����������������������е���  
        id: circle  
        //anchors.fill: parent  
        property real radius: 0                                        // ��������radius  
        property real dx: root.width / 2                               // Բ�ĺ�����dx  
        property real dy: root.height / 2                              // Բ��������dy     
        property real cx: radius * Math.sin(percent*6.283185307179) + dx  // ���㵱ǰ������cx  
        property real cy: radius * Math.cos(percent*6.283185307179) + dy  // ���㵱ǰ������cy  
        property real percent: 0                                       // �ٷֱ�percent  
  
        SequentialAnimation on percent {                               // ʹ�����������ı�<span style="font-family: Arial, Helvetica, sans-serif;">�Զ�������percent</span>  
  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation {                                          // ��ֵ������ע�⵽���������������ʹ����˳ʱ�롢��ʱ�뽻���˶���ʵ��Ч��Ҳ�����  
            duration: 1000  
            from: 1  
            to: 0  
            loops: 8  
            }  
            NumberAnimation {  
            duration: 1000  
            from: 0  
            to: 1  
            loops: 8  
            }  
  
        }  
  
        SequentialAnimation on radius {                // �뾶�Ķ���  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation {  
                duration: 4000  
                from: 0  
                to: 100  
            }  
            NumberAnimation {  
                duration: 4000  
                from: 100  
                to: 0  
            }  
        }  
    }  
  
    Item {                                 // ��Ȧ����ʽ�˶���������Ҫ�����߼���������乫ת����ת  
        id: circle3  
        property real radius: 100  
        property real dx: root.width / 2  
        property real dy: root.height / 2  
        property real cx: radius * Math.sin(percent*6.283185307179) + dx  
        property real cy: radius * Math.cos(percent*6.283185307179) + dy  
        property real percent: 0  
  
        SequentialAnimation on percent {             // ����İٷֱȽ�ʹ��һ��ѭ�����Ͳ������˳��ʱ��Ľ����˶�  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation { from: 0.0; to: 1 ; duration: 10000;  }  
        }  
    }  
  
    Item {  
        id: circle2  
        property real radius: 30  
        property real dx: circle3.cx               // ע�������Բ�ľͲ�������ĻԲ����  
        property real dy: circle3.cy  
        property real cx: radius * Math.sin(percent*6.283185307179) + dx  
        property real cy: radius * Math.cos(percent*6.283185307179) + dy  
        property real percent: 0  
  
        SequentialAnimation on percent {  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation { from: 0.0; to: 1 ; duration: 1000; }  
        }  
    }  
  
}  