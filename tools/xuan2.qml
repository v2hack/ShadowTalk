import QtQuick 2.0  
import QtQuick.Particles 2.0  
  
Rectangle {                                        // 还是矩形背景，不过定义了一个属性用来进行逻辑判断  
    width: 320  
    height: 480  
    color: "black"  
    property bool lastWasPulse: false  
    Timer {  
        interval: 3500                     // 3.5秒定时器  
        triggeredOnStart: true  
        running: true  
        repeat: true  
        onTriggered: {  
        //! [0]  
            if (lastWasPulse) {             // 如果上次是脉冲  
                burstEmitter.burst(500);    // burstEmitter调用burst发射500个粒子（一次）  
                lastWasPulse = false;  
            } else {  
                pulseEmitter.pulse(500);    // 这里的pulse(500)会先检查pulseEmitter是否在运行，如果没有则会将它激活500毫秒，然后停止。所以虽然pulseEmitter和burstEmitter的代码一模一样，但粒子效果不同，由于Emitter每秒发射1000个粒子，0.5秒也是500个，但它是在一个持续时间内发射的，因此粒子带相对burstEmitter更宽。  
                lastWasPulse = true;  
            }  
        //! [0]  
        }  
    }  
    ParticleSystem {                        // 这里将ParticleSystem作为ImageParticle、Emitter的父对象，它们就不再需要指定系统  
        id: particles  
        anchors.fill: parent  
        ImageParticle {                     // 基本图像粒子  
            source: "qrc:///particleresources/star.png"  
            alpha: 0  
            colorVariation: 0.6             // 0.6保证了丰富的色彩  
        }  
  
        Emitter {                           // 与上面的例子不同，这个粒子系统包含两个发射器  
            id: burstEmitter  
            x: parent.width/2               // 最主要的是，这里的Emitter没有了属性绑定，因此需要在定时器中手动调用burst和pulse  
            y: parent.height/3  
            emitRate: 1000  
            lifeSpan: 2000  
            enabled: false  
            velocity: AngleDirection{magnitude: 64; angleVariation: 360}  // 这里使用了AngleDirection以使用角度定义粒子行为，magnitude指明了在该角度的每秒运动距离（像素），angleVariation使粒子方向随机从0到其大小之间产生。这里也就是一个圆  
            size: 24  
            sizeVariation: 8  
            Text {  
                anchors.centerIn: parent      
                color: "white"  
                font.pixelSize: 18  
                text: "Burst"  
            }  
        }  
        Emitter {  
            id: pulseEmitter  
            x: parent.width/2  
            y: 2*parent.height/3  
            emitRate: 1000  
            lifeSpan: 2000  
            enabled: false  
            velocity: AngleDirection{magnitude: 64; angleVariation: 360}  
            size: 24  
            sizeVariation: 8  
            Text {  
                anchors.centerIn: parent  
                color: "white"  
                font.pixelSize: 18  
                text: "Pulse"  
            }  
        }  
    }  
}  