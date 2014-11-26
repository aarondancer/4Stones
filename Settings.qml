import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

Rectangle {
    id: settings
    property int divisor: (height < width ? height : width)

    ListModel {
        id: backgroundModel
        ListElement {
            image: "forest.jpg"
        }
        ListElement {
            image: "kite.jpg"
        }
        ListElement {
            image: "ripples.png"
        }
    }

    Component {
         id: backgroundDelegate
         Column {
             id: wrapper
             Image {
                 width: 64;
                 height: 64
                 source: image
             }
         }
    }

    Image{ //Background, uses image for now
        id: settingsBackground
        z: 0
        height: parent.height
        width: parent.width
        source: backgroundSource
        fillMode: Image.PreserveAspectCrop
        Rectangle{
            width: parent.width
            height: parent.height
            //color: Qt.rgba(0,0,0,0.3)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "grey" }
                GradientStop { position: 1; color: "transparent" }
            }
        }
    }

    Label{
        id: settingsLabel
        font.pointSize: divisor / 4
        text: "Settings"
        color: "white"
        x: -30;
        font.weight: Font.Light
        font.family: "Helvetica Neue"
    }

    PathView{
        id: backgroundSelection
        height: settings.height - settingsLabel.height
        width: settings.width
        model: backgroundModel
        delegate: delegate
        path: Path {
            startX: 120; startY: 100
            PathQuad { x: 120; y: 25; controlX: 260; controlY: 75 }
            PathQuad { x: 120; y: 100; controlX: -20; controlY: 75 }
        }
    }
}
