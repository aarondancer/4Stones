import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

Rectangle {
    id: difficultyMenu
    property int divisor: (height < width ? height : width)

    Image{ //Background, uses image for now
        id: difficultyBackground
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

    Column{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: divisor / 12
        Row{
            spacing: divisor / 12
            Button{
                id: easyButton
                text: "Easy"
                width: height
                height: divisor/ 3
                onClicked: {TheForce.selectDifficulty(1);}
                style: ButtonStyle{
                    label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Helvetica"
                        font.weight: Font.Light
                        font.pointSize: control.height / 6
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
                id: mediumButton
                text: "Medium"
                width: height
                height: divisor/ 3
                onClicked: {TheForce.selectDifficulty(2);}
                style: ButtonStyle{
                    label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Helvetica"
                        font.weight: Font.Light
                        font.pointSize: control.height / 6
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

        Row{
            spacing: divisor / 12
            Button{
                id: hardButton
                text: "Hard"
                width: height
                height: divisor/ 3
                onClicked: {TheForce.selectDifficulty(3);}
                style: ButtonStyle{
                    label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Helvetica"
                        font.weight: Font.Light
                        font.pointSize: control.height / 6
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

            Button{
                id: humanButton
                text: "Play with a Friend"
                width: height
                height: divisor/ 3
                onClicked: {TheForce.selectDifficulty(4);}
                style: ButtonStyle{
                    label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Helvetica"
                        font.weight: Font.Light
                        font.pointSize: control.height / 6
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
                        color: (!control.hovered) ? "grey" : Qt.lighter("grey", 1.2)
                    }
                }
            }

        }

    }

}
