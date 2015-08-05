import QtQuick 2.0  
import QtQuick.Particles 2.0  
  
Rectangle {                                        // ���Ǿ��α���������������һ���������������߼��ж�  
    width: 320  
    height: 480  
    color: "black"  
    property bool lastWasPulse: false  
    Timer {  
        interval: 3500                     // 3.5�붨ʱ��  
        triggeredOnStart: true  
        running: true  
        repeat: true  
        onTriggered: {  
        //! [0]  
            if (lastWasPulse) {             // ����ϴ�������  
                burstEmitter.burst(500);    // burstEmitter����burst����500�����ӣ�һ�Σ�  
                lastWasPulse = false;  
            } else {  
                pulseEmitter.pulse(500);    // �����pulse(500)���ȼ��pulseEmitter�Ƿ������У����û����Ὣ������500���룬Ȼ��ֹͣ��������ȻpulseEmitter��burstEmitter�Ĵ���һģһ����������Ч����ͬ������Emitterÿ�뷢��1000�����ӣ�0.5��Ҳ��500������������һ������ʱ���ڷ���ģ�������Ӵ����burstEmitter����  
                lastWasPulse = true;  
            }  
        //! [0]  
        }  
    }  
    ParticleSystem {                        // ���ｫParticleSystem��ΪImageParticle��Emitter�ĸ��������ǾͲ�����Ҫָ��ϵͳ  
        id: particles  
        anchors.fill: parent  
        ImageParticle {                     // ����ͼ������  
            source: "qrc:///particleresources/star.png"  
            alpha: 0  
            colorVariation: 0.6             // 0.6��֤�˷ḻ��ɫ��  
        }  
  
        Emitter {                           // ����������Ӳ�ͬ���������ϵͳ��������������  
            id: burstEmitter  
            x: parent.width/2               // ����Ҫ���ǣ������Emitterû�������԰󶨣������Ҫ�ڶ�ʱ�����ֶ�����burst��pulse  
            y: parent.height/3  
            emitRate: 1000  
            lifeSpan: 2000  
            enabled: false  
            velocity: AngleDirection{magnitude: 64; angleVariation: 360}  // ����ʹ����AngleDirection��ʹ�ýǶȶ���������Ϊ��magnitudeָ�����ڸýǶȵ�ÿ���˶����루���أ���angleVariationʹ���ӷ��������0�����С֮�����������Ҳ����һ��Բ  
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