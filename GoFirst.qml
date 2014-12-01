import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

Rectangle {
    id: goFirst
    property int divisor: (height < width ? height : width)

    Image{ //Background, uses image for now
        id: goFirstBackground
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

    Row{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: divisor / 12
        Button{
            id: firstButton
            text: "Username"
            width: height
            height: divisor/ 3
            onClicked: {TheForce.whoGoesFirst(1);}
            style: ButtonStyle{
                label: Text {
                    renderType: Text.QtRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Helvetica"
                    font.weight: Font.Light
                    font.pixelSize: control.height / 6
                    color: "white"
                    text: control.text
                    wrapMode: Text.WordWrap
                }
                background: Rectangle {
                        width: control.width
                        height:  control.height
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "white"
                        radius: width *0.5
                        color: (!control.hovered) ? blue : Qt.lighter(blue, 1.2)
                }
            }
        }

        Button{
            id: secondButton
            text: "Player 2"
            width: height
            height: divisor/ 3
            onClicked: {TheForce.whoGoesFirst(-1);}
            style: ButtonStyle{
                label: Text {
                    renderType: Text.QtRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Helvetica"
                    font.weight: Font.Light
                    font.pixelSize: control.height / 6
                    color: "white"
                    text: control.text
                    wrapMode: Text.WordWrap
                }
                background: Rectangle {
                    width: control.width
                    height:  control.height
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "white"
                    radius: width *0.5
                    color: (!control.hovered) ? red : Qt.lighter(red, 1.2)
                }
            }
        }
    }
    onVisibleChanged: {
        firstButton.text = (player.username !== "") ? player.username : "Player 1";
        switch(computer.difficulty){
        case 1:
            secondButton.text = "Easy AI";
            break;
        case 2:
            secondButton.text = "Medium AI";
            break;
        case 3:
            secondButton.text = "Hard AI";
            break;
        case 4:
            secondButton.text = "Player 2";
        }
    }
}
