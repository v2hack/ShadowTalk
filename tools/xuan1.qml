import QtQuick 2.0  
import QtQuick.Particles 2.0   
  
Rectangle {                                           // 矩形根元素  
  
    id: root  
  
    height: 540  
    width: 360  
  
    gradient: Gradient {                              // 加入渐变效果  
        GradientStop { position: 0; color: "#000020" }  
        GradientStop { position: 1; color: "#000000" }  
    }  
  
    MouseArea {                                       // 为了实现点击效果加入  
        id: mouseArea  
        anchors.fill: root  
    }  
  
    ParticleSystem { id: sys1 }                         // 基于ParticleSystem的粒子特效  
    ImageParticle {                                     // 也是粒子系统的基本元素  
        system: sys1                                    // 指明系统  
        source: "qrc:///particleresources/glowdot.png"  // 这里选用了"光点"粒子，详细内容见下方第（1）点  
        color: "cyan"                                   // 颜色  
        alpha: 0                                        // 透明度  
        SequentialAnimation on color {                  // 在颜色上加入动画  
            loops: Animation.Infinite                   // 无限循环，等同-1，如果是正值则循环具体次数  
            ColorAnimation {                            // 颜色动画  
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
        colorVariation: 0.3                             // 颜色变化率，从0到1，越大粒子群的色彩越丰富  
    }  
    //! [0]  
    Emitter {                                                  // 这就是我们的发射器了  
        id: trailsNormal  
        system: sys1                                           // 一样要指明具体的粒子系统  
  
        emitRate: 500                                          // 每秒粒子发射数  
        lifeSpan: 2000                                         // 粒子生命周期(毫秒)  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle.cy       // 发射到的坐标值  
        x: mouseArea.pressed ? mouseArea.mouseX : circle.cx       // 这里使用mouseArea检测是否按下，有则使用按下的坐标，否则使用下面的计算坐标。这里的粒子之所以能够持续的发射，其缘由正是QML的属性绑定，由于这个坐标值的持续变化，造成了我们所见的粒子动画。  
  
  
        velocity: PointDirection {xVariation: 4; yVariation: 4;}  // 当粒子产生后，其扩散行为在x,y方向上的速度  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;} // 扩散行为的加速度  
        velocityFromMovement: 8                                   // 基于当前粒子的运动为其添加一个额外的速度向量  
  
        size: 8                                                   // 粒子大小，单位是像素，默认为16  
        sizeVariation: 4                                          // 一个会随机加到size和endSize上的增量  
    }  
    //! [0]                                                        
    ParticleSystem { id: sys2 }                                   // 第二个粒子系统，与前者大同小异  
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
        source: "qrc:///particleresources/star.png"               // 这里选取了一种不同的粒子，star更小更亮且具有两条发亮的对角线  
    }  
    Emitter {  
        id: trailsStars  
        system: sys2  
  
        emitRate: 100                                            // 较少的星星掺杂在光点中，达到绚丽的效果  
        lifeSpan: 2200  
  
  
        y: mouseArea.pressed ? mouseArea.mouseY : circle.cy  
        x: mouseArea.pressed ? mouseArea.mouseX : circle.cx  
  
        velocity: PointDirection {xVariation: 4; yVariation: 4;}  
        acceleration: PointDirection {xVariation: 10; yVariation: 10;}  
        velocityFromMovement: 8  
  
        size: 22  
        sizeVariation: 4  
    }  
    ParticleSystem { id: sys3; }                                // 螺旋运动的粒子  
    ImageParticle {  
        source: "qrc:///particleresources/glowdot.png"  
        system: sys3  
        color: "orange"                                       
        alpha: 0  
        SequentialAnimation on color {                         // 初始值为橙色，但颜色动画仅需在红绿间切换，因为橙色是其过渡色  
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
  
        colorVariation: 0.2                                 // 如果这个值是1，就看不出上述的动画效果了，如果为0，粒子群的颜色显得单调  
  
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
  
  
  
    color: "white"                                                     // 不明白这个color的意义，因为矩形的颜色在渐变那里已经被确定了  
  
    Item {                                                             // 我们可以使用Item来包含一个逻辑对象，并为它命名，定义其属性来进行调用  
        id: circle  
        //anchors.fill: parent  
        property real radius: 0                                        // 定义属性radius  
        property real dx: root.width / 2                               // 圆心横坐标dx  
        property real dy: root.height / 2                              // 圆心纵坐标dy     
        property real cx: radius * Math.sin(percent*6.283185307179) + dx  // 计算当前横坐标cx  
        property real cy: radius * Math.cos(percent*6.283185307179) + dy  // 计算当前纵坐标cy  
        property real percent: 0                                       // 百分比percent  
  
        SequentialAnimation on percent {                               // 使用连续动画改变<span style="font-family: Arial, Helvetica, sans-serif;">自定义属性percent</span>  
  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation {                                          // 数值动画，注意到这里的往复动画会使粒子顺时针、逆时针交替运动，实际效果也是如此  
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
  
        SequentialAnimation on radius {                // 半径的动画  
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
  
    Item {                                 // 外圈螺旋式运动的粒子需要两个逻辑对象控制其公转与自转  
        id: circle3  
        property real radius: 100  
        property real dx: root.width / 2  
        property real dy: root.height / 2  
        property real cx: radius * Math.sin(percent*6.283185307179) + dx  
        property real cy: radius * Math.cos(percent*6.283185307179) + dy  
        property real percent: 0  
  
        SequentialAnimation on percent {             // 这里的百分比仅使用一个循环，就不会产生顺逆时针的交替运动  
            loops: Animation.Infinite  
            running: true  
            NumberAnimation { from: 0.0; to: 1 ; duration: 10000;  }  
        }  
    }  
  
    Item {  
        id: circle2  
        property real radius: 30  
        property real dx: circle3.cx               // 注意这里的圆心就不再是屏幕圆心了  
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