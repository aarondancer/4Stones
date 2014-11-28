import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce
import "QChart.js" as Charts

Rectangle {
    id: history
    property int divisor: (height < width ? height : width)
    signal back;

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
            MouseArea{
                anchors.fill: parent;
                onClicked: { history.back(); }
            }
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
        text: player.username
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica Neue"
        font.letterSpacing: 5
    }
    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        QChart{
            id: yummyPie;
            width: divisor * 0.75;
            height: width;
            chartType: Charts.ChartType.PIE;
            opacity: 0.75
            //      anchors.top: historyLabel.bottom
            chartAnimated: false;
            contextType: "2d"
            Component.onCompleted: {
                chartData = [{
                               value: player.wins,
                               color: blue
                            }, {
                               value: player.losses,
                               color: red
                            }, {
                               value: player.draws,
                               color: "grey"
                           }];
            }
        }
        Label{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Wins: " + player.wins
            color: blue
            horizontalAlignment: Text.Center
            font.pointSize: historyLabel.font.pointSize / 3
        }
        Label{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Losses: " + player.losses
            color: red
            horizontalAlignment: Text.Center
            font.pointSize: historyLabel.font.pointSize / 3
        }
        Label{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Draws: " + player.draws
            color: "grey"
            horizontalAlignment: Text.Center
            font.pointSize: historyLabel.font.pointSize / 3
        }
    }

    onVisibleChanged: init();

    function init(){
        historyLabel.text = player.username

    }
}
