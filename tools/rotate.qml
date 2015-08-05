import QtQuick 2.4
  
Rectangle{  
    id:page  
    width:500;height:200  
    color:"green"  
    Text{  
        id:mytext  
        text:"Welcome to China"  
        y:30  
        anchors.horizontalCenter: page.horizontalCenter  
        font.pointSize: 24;font.bold: true;color:"yellow"  
        MouseArea{id:mouseArea;anchors.fill: parent}  
        states:State{  
            name:"down";when:mouseArea.pressed==true  
            PropertyChanges {  
                target: mytext;y:150;rotation:180;color:"red"  
            }  
        }  
        transitions:Transition {  
                from: ""  
                to: "down"  
                reversible: true  
                ParallelAnimation{  
                    NumberAnimation{properties: "y,rotation";duration:500;easing.type:Easing.InOutQuad}  
                    ColorAnimation { duration:500 }  
                }  
        }  
    }  
} 