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
        anchors.topMargin: history.height / 48
        font.pointSize: divisor / 8
        text: player.username
        color: "white"
        font.weight: Font.Light
        font.family: "Helvetica"
        font.letterSpacing: 5
    }

    Button{
        id: deleteButton
        anchors.right: history.right
        anchors.top: history.top
        anchors.margins: history.height / 48
        text: "Delete " + player.username
        width: height
        height: historyLabel.height
        onClicked: {
            deleteDialog.visible = true;
        }

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
                color: (!control.hovered) ? "grey" : Qt.lighter("grey")
            }
        }
    }

    Column{
        anchors.top: historyLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle{
            color: "transparent"
            width: 1;
            height: (history.height - historyContent.height - historyLabel.height - (history.height / 48)) / 2
        }

        Column{
            id: historyContent
            anchors.horizontalCenter: parent.horizontalCenter

            QChart{
                id: yummyPie;
                width: (divisor- historyLabel.height) * 0.75;
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

            Rectangle{
                color: "transparent"
                width: 1;
                height: history.height / 48
            }

            Label{
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Wins: " + player.wins
                color: blue
                horizontalAlignment: Text.Center
                font.pointSize: historyLabel.font.pointSize / 2.5
            }
            Label{
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Losses: " + player.losses
                color: red
                horizontalAlignment: Text.Center
                font.pointSize: historyLabel.font.pointSize / 2.5
            }
            Label{
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Draws: " + player.draws
                color: "grey"
                horizontalAlignment: Text.Center
                font.pointSize: historyLabel.font.pointSize / 2.5
            }

            Rectangle{
                color: "transparent"
                width: 1;
                height: history.height / 48
            }
        }
    }

    FSDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: deleteDialog
        title: "Are you sure?"
        message: "Are you sure that you would like to delete the account: " + player.username + " ?";
        cancel: true
        accept: true
        decline: false
        visible: false
        z: 1010

        onCanceled: {
            visible = false;
        }

        onAcceptChanged: {
            player.deletePlayer();
            visible = false;
        }

        onVisibleChanged: { menusOpen = (visible) ? menusOpen + 1 : menusOpen - 1; }
    }

    onVisibleChanged: init();

    function init(){
        historyLabel.text = player.username

    }
}
