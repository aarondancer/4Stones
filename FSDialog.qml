import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtGraphicalEffects 1.0

Rectangle {
    signal canceled;
    signal accepted;
    signal declined;

    property string title;
    property string message;

    property bool cancel;
    property bool accept;
    property bool decline;

    property string cancelText: "Cancel";
    property string acceptText: "Yes";
    property string declineText: "No";

    property int divisor: (height < width ? height : width)
    color: Qt.rgba(0,0,0,0.5);
    id: dialogBackground
    width: parent.width
    height: parent.height

    RectangularGlow{
        id: glow
        anchors.fill: dialog
        glowRadius: 10
        spread: 0.2
        color: Qt.rgba(0,0,0,0.25);
        cornerRadius: dialog.radius + glowRadius
    }

    Rectangle{
        id: dialog
        width: divisor * 0.75
        height: width * 0.75
        color: Qt.rgba(255,255,255,0.85);
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 10;

        Column{
            anchors.horizontalCenter: dialog.horizontalCenter
            height: parent.height
            width: parent.width
            Rectangle{
                height: buttonRow.height / 2
                width: 1;
                color: "transparent"
            }

            Label{
                text: title;
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: divisor / 16
                renderType: "QtRendering"
            }

            Rectangle{
                height: buttonRow.height / 4
                width: 1;
                color: "transparent"
            }

            Label{
                text: message;
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: divisor / 32
                font.weight: Font.Light
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.Center
                width: dialog.width - 40
                renderType: "QtRendering"
            }
        }

        Row{
            id: buttonRow
            anchors.horizontalCenter: dialog.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: height / 2
            spacing: divisor / 12
            Button{
                id: cancelButton
                text: cancelText
                width: height
                height: dialog.height / 4
                onClicked: dialogBackground.canceled()
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
                            color: (!control.hovered) ? "grey" : Qt.lighter("grey", 1.2)
                    }
                }
                visible: cancel;
            }

            Button{
                id: noButton
                text: declineText
                width: height
                height: dialog.height / 4
                onClicked: dialogBackground.declined()
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
                visible: decline;
            }

            Button{
                id: yesButton
                text: acceptText
                width: height
                height: dialog.height / 4
                onClicked: dialogBackground.accepted()
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
                visible: accept;
            }
        }
    }
}


