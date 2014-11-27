import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

Rectangle {
    id: history
    property int divisor: (height < width ? height : width)

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


    Rectangle{
        width: backArrow.width
        height: backArrow.height
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        color: "transparent"
        Image{
            id: backArrow
            source:"back arrow.svg"
            sourceSize: Qt.size(width, width)
            width: height
            height: historyLabel.paintedHeight
        }

        ColorOverlay{
            source: backArrow
            anchors.fill: backArrow
            color: "white"
        }
    }

    Label{
        id: historyLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: divisor / 8
        text: player.wins
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica Neue"
        font.letterSpacing: 5
    }

    onVisibleChanged: init();

    function init(){
        historyLabel.text = player.username
    }
}
