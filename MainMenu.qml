import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import "theForce.js" as TheForce


Rectangle {
    id: menu
    width: parent.width
    height: parent.height
    property int divisor: (parent.height < parent.width ? parent.height : parent.width)
    Column{
        spacing: 12
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: -fsrow.height / 2

        Row{ //Because stupid CSS styling isn't working >:(
            id: fsrow
            Label{
                text: "4"
                font.pixelSize: divisor / 8
                font.family: "Century Gothic"
                font.weight: Font.Light
                color: red
            }
            Label{
                text: "stones"
                font.pixelSize: divisor / 8
                font.family: "Century Gothic"
                font.weight: Font.Light
                color: blue
            }
        }

        Label{
            text: "Back"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {menu.visible = false}
            }
        }
        Label{
            text: "New Game"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {menu.visible = false}
            }
        }
        Label{
            text: "Restart"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {TheForce.boardReset(); /*menu.visible = false;*/}
            }
        }
        Label{
            text: "Settings"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {settings.visible = true}
            }
        }
    }
}
