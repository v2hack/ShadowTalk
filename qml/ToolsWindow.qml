import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

//import "functions.js" as Helper

Column {
    width: 100
    height: 100

    ToolButton {
        text: "Adjust contrast"
//        background: "img/contrast.png"
        onClicked: toolbox.openWindow("Contrast")
    }


}
