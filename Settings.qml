import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import com.FourStones.qmlcomponents 1.0
import "theForce.js" as TheForce

Rectangle {
    id: settings
    property int divisor: (height < width ? height : width)
    property bool loaded: false;
    property int savedIndex;

    SettingsHelper{
        id: settingsHelper
        Component.onCompleted: {
            for (var i = 0; i < wallpapers.count; i++){
                if (wallpapers.get(i).image === getValue("background", "forest.jpg")){
                    wallpaperSlider.currentIndex = i;
                    savedIndex = i;
                    backgroundSource = wallpapers.get(i).image;
                    loaded = true;
                }
            }
        }
    }

    ListModel {
        id: wallpapers
        ListElement { name: "Kite"; image: "kite.jpg" }
        ListElement { name: "Ripples"; image: "ripples.png" }
        ListElement { name: "Forest"; image: "forest.jpg" }
        ListElement { name: "Cityscape"; image: "cityscape.png" }
        ListElement { name: "Envelopes"; image: "envelopes.png" }
        ListElement { name: "Rainbow"; image: "rainbow.jpg" }
    }

    Component {
        id: wallpaperDelegate
        Item {
            width: divisor; height: divisor

            Image {
                id: wallpaper
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: divisor * 0.05
                width: parent.width * 0.9
                fillMode: Image.PreserveAspectFit
                source: image
                smooth: true
            }

            Label{
                id: wallpaperLabel
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: wallpaper.bottom
                anchors.topMargin: divisor / 48
                font.pixelSize: divisor / 16
                text: name
                color: "white"
                font.weight: Font.Light
                font.family: "Helvetica"
                font.letterSpacing: 5
            }

//            MouseArea {
//                anchors.fill: parent
//                onClicked: coverFlow.currentIndex = index
//            }
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
                onClicked: {
                    settings.visible = false;
                    mainMenu.enable();
                }
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
        anchors.topMargin: settings.height / 48
        font.pixelSize: divisor / 8
        text: "Settings"
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica"
        font.letterSpacing: 5
    }

    Label{
        id: selectWallpaper
        anchors.top: settingsLabel.bottom
        anchors.topMargin: divisor / 32
        anchors.left: settings.left
        anchors.leftMargin: divisor * 0.05
        font.pixelSize: divisor / 12
        text: "Wallpaper: "
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica"
        font.letterSpacing: 5
    }

    ListView {
        id: wallpaperSlider
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectWallpaper.bottom
        anchors.topMargin: divisor / 32
        Keys.onRightPressed: incrementCurrentIndex();
        Keys.onLeftPressed: decrementCurrentIndex();
        orientation: ListView.Horizontal
        focus: true
        model: wallpapers
        delegate: wallpaperDelegate
        width: divisor
        height: divisor / 2
        spacing: divisor * 0.05
        interactive: true
        flickableDirection: Flickable.HorizontalFlick
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightFollowsCurrentItem: true;
        onCurrentIndexChanged: {
            if(settings.enabled){
                savedIndex = currentIndex;
            }else{
                currentIndex = savedIndex;
            }

            if (loaded) {
                backgroundSource = wallpapers.get(currentIndex).image;
                settingsHelper.setValue("background", backgroundSource);
            }
        }
    }

    onVisibleChanged: {
        if (settings.visible) settings.enabled = true;
        else settings.enabled = false;
    }
}
