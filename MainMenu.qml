import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import "theForce.js" as TheForce

Rectangle {
    id: menu
    width: parent.width
    height: parent.height
    property int divisor: (height < width ? height : width)

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
            id: backButton
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
            id: historyButton
            text: player.username
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: { /*history.visible = true*/
                    historyLoader.visible = true;
                    historyLoader.source = "History.qml"
                    menusOpen = menusOpen + 1;
                    disable();
                }
            }

            onTextChanged: {
                visible = !(player.username === "");
            }
        }

        Label{
            id: newGameButton
            text: "New Game"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    TheForce.showDifficulties();
                }
            }
        }


        Label{
            id: restartButton
            text: "Restart"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    TheForce.boardReset();
                }
            }
        }

        Label{
            id: settingsButton
            text: "Settings"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: { settings.visible = true; disable();}
            }
        }

        Label{
            id: logoutButton
            text: "Logout"
            color: "white"
            font.pixelSize: divisor / 12
            font.family: "Helvetica"
            font.weight: Font.Light
            MouseArea{
                z: 1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    player.logout();
                    login.visible = true;
                }
            }
        }
    }

    Loader {
        id: historyLoader
        anchors.fill: parent
    }

    Connections {
        target: historyLoader.item
        onBack: {
            historyLoader.source = "";
            menusOpen = menusOpen - 1;
            enable();
        }
    }

    onVisibleChanged: {
        historyButton.text = player.username;
    }

    function hideHistory(){
        historyButton.visible = false
    }

    function disable(){
        backButton.enabled = false;
        restartButton.enabled = false;
        newGameButton.enabled = false;
        historyButton.enabled = false;
        logoutButton.enabled = false;
        settingsButton.enabled = false;
    }

    function enable(){
        backButton.enabled = true;
        restartButton.enabled = true;
        newGameButton.enabled = true;
        historyButton.enabled = true;
        logoutButton.enabled = true;
        settingsButton.enabled = true;
    }
}
