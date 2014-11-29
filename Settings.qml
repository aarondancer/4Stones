import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

Rectangle {
    id: settings
    property int divisor: (height < width ? height : width)
    signal back;

    ListModel {
        id: wallpapers
        ListElement { image: "kite.jpg" }
        ListElement { image: "ripples.png" }
        ListElement { image: "forest.jpg" }
    }

    Component {
        id: wallpaperDelegate
        Item {
            width: settings.width; height: settings.height / 2

            Image {
                id: wallpaper
                width: parent.width * 0.9
                height: parent.height
                fillMode: Image.PreserveAspectFit
                source: image
                smooth: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: coverFlow.currentIndex = index
            }
        }
    }

    Image{ //Background, uses image for now
        id: historyBackground
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
            height: settingsLabel.paintedHeight
            MouseArea{
                anchors.fill: parent;
                onClicked: { settings.back(); }
            }
        }

        ColorOverlay{
            source: backArrow
            anchors.fill: backArrow
            color: "white"
        }
    }

    Label{
        id: settingsLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: divisor / 8
        text: "Settings"
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica Neue"
        font.letterSpacing: 5
    }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: settingsLabel.bottom
        Keys.onRightPressed: incrementCurrentIndex()
        Keys.onLeftPressed: decrementCurrentIndex()
        orientation: ListView.Horizontal
        id: coverFlow
        focus: true
        model: wallpapers
        delegate: wallpaperDelegate
        width: settings.width * 0.9
        height: settings.height / 2
        spacing: settings.width * 0.05
        interactive: true
        flickableDirection: Flickable.HorizontalFlick
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange

        onCurrentIndexChanged: {
            backgroundSource = wallpapers.get(currentIndex).image
        }
    }
}
