import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import com.FourStones.qmlcomponents 1.0
import QtQuick.Controls 1.2

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 960
    title: "4Stones"

    property int turn: 1;
    property color turnColor: blue;
    property color blue: "#3359E7"
    property color red: "#FC2833"
    property bool isVisible: false
    property string backgroundSource: "forest.jpg"

    property Grid board: Grid{
        id: board;
        objectName: "boardo"
        gridLength: 5;
        countToWin: 4;
    }

    Component { //This is the component for the tiles
        id: tileDelegate
            Column { //Column makes sure that each sell is in separate column
                Rectangle { //The cell
                    id: tile
                    width: gridView.cellWidth; height: gridView.cellHeight;
                    border.color: Qt.rgba(0.1,0.1,0.1,0.8)
                    color: "transparent"
                    antialiasing: true

                    Rectangle { //The stone
                        id: stone
                        width: parent.height - 10
                        height: width
                        color: "transparent"
                        border.color: "white"
                        border.width: 0
                        radius: width * 0.5
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        antialiasing: true
                        opacity: 0;
                    }

                    MouseArea { //Make the cell clickable
                        id: tileMouseArea
                        z: 1
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked:{
                            if (isVisible && board.valueFromIndex(index) === 0){
                                lastMoveCheck();
                                board.placePiece(index, turn);
                                lastMoveCheck();
                                winDialog.visible = board.checkWin(turn);
                                turn = (turn === 1) ? 2 : 1;
                            }
                            function lastMoveCheck(){
                                if (board.valueFromIndex(board.lastMove) !== 0){
                                    stone.color = (board.valueFromIndex(board.lastMove) === 1) ? blue : red;
                                    turnColor = (board.valueFromIndex(board.lastMove) === 2) ? blue : red;
                                    stone.border.width = 1;
                                    stone.opacity = 1;
                                }
                            }
                        }
                        onEntered: {
                            if(isVisible && board.valueFromIndex(index) === 0){
                                stone.color = (turn === 1) ? Qt.lighter(blue, 1.3) : Qt.lighter(red, 1.3);
                                stone.border.width = 1;
                                animateOpacityUp.start();
                            }
                        }
                        onExited: {
                            if(isVisible && board.valueFromIndex(index) === 0) animateOpacityDown.start();
                        }

                        NumberAnimation { id:animateOpacityUp; target: stone; property: "opacity"; to: 1.0; duration: 350 }

                        NumberAnimation { id:animateOpacityDown; target: stone; property: "opacity"; to: 0; duration: 150; onRunningChanged: {
                                if (!animateOpacityDown.running) { stone.color = "transparent"; stone.border.width = 0; stone.opacity = 0}}
                        }
                    }
                }
            }
    }

    //The stuff below is actually on the view

    Image{ //Background, uses image for now
        id: background
        z: 0
        height: parent.height
        width: parent.width
        source: backgroundSource
        fillMode: Image.PreserveAspectCrop
    }

    Rectangle{ //The main view
        id: mainView
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.lighter(turnColor, 1.5) }
            GradientStop { position: 1; color: "transparent" }
        }
        antialiasing: true

        Column{ //Column for stacked layout
            width: parent.width - 20
            height: parent.height - 20
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle{ //Spacer
                height: (parent.height/2 - gridView.height) / 2
                width: parent.width
                color: "transparent"
            }

            Row{ //This is the top quarter. Row for side-by-side layout
                width: (parent.height / 2 < parent.width ? parent.height / 2 : parent.width)
                height: (parent.height < parent.width ? parent.height : parent.width) / 4
                anchors.horizontalCenter: parent.horizontalCenter

                Image{ //The logo
                    id: logo
                    width: parent.width * 0.25
                    height: width
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    smooth: true
                    source: "4Stones.png"
                }

                Rectangle{ //Spacer to justify the menu button right
                    width: parent.width * 5/8
                    height: parent.height
                    color: "transparent"
                }

                Label { //Menu button made with Label
                    id: menuButton
                    anchors.verticalCenter: parent.verticalCenter
                    text: "≡"
                    font.pixelSize: parent.width / 8
                    font.bold: true

                    MouseArea{ //Makes the Label clickable
                        z: 1
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: {if (!mainMenu.visible) mainMenu.visible = !mainMenu.visible;}
                    }
                }
            }

            Rectangle{ //Spacer
                height: (parent.height/2 - gridView.height) / 2
                width: parent.width
                color: "transparent"
            }

            Rectangle{ //Rectangle houses the grid, provides the outer border
                width: (parent.height / 2 < parent.width ? parent.height / 2 : parent.width) + border.width
                height: width
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.preferredHeight: width
                Layout.preferredWidth: width
                color: Qt.rgba(0,0,0,0.15)
                border.color: "black"
                border.width: 3
                radius: 5

                GridView { //this is the grid
                    id: gridView
                    width: parent.width - parent.border.width
                    height: parent.height - parent.border.width
                    antialiasing: true
                    boundsBehavior: Flickable.StopAtBounds; flow: GridView.FlowLeftToRight
                    cellHeight: width / board.gridLength; cellWidth: cellHeight
                    focus: true
                    model: board.gridLength * board.gridLength
                    delegate: tileDelegate
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Row{ //Undo button area
                height: 20
                Rectangle{
                    color: "transparent"
                    height: 10
                    width: (mainWindow.width - gridView.width) / 2
                }

                Label{
                    text: "↩"
                    width: gridView.width
                    height: parent.height
                    font.pixelSize: height * 2.5
                    MouseArea{
                        onClicked: {}
                    }
                }
            }

            Rectangle{ //Spacer
                height: (parent.height/2 - gridView.height) + 10
                width: parent.width
                color: "transparent"
            }

            Rectangle{ //Rectangle houses How-to text. Still working out the dynamicness #engrish
                width: gridView.width
                height: howTo.height
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

                Text{ //how-to text
                    id: howTo
                    //anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: Text.contentHeight
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    text: "<html><b><u>How to play:</b></u> Players take turns placing stones. The first player to get 4 stones in a row wins!</html>"
                    wrapMode: Text.WordWrap
                    font.pixelSize: ((mainWindow.width > mainWindow.height)? mainWindow.height :mainWindow.width) / 32
                    font.family: "Helvetica"
                }
            }
        }
    }

    MessageDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: winDialog
        title: "Winner!"
        text: "Winner!"
        informativeText: "Player " + ((turn == 1) ? 2 : 1) + " wins!"
        onAccepted: ;
    }

    MainMenu{ //Main Menu
        id: mainMenu
        z: 100
        color: Qt.rgba(0,0,0,0.75)
        visible: false
        onVisibleChanged: isVisible = !visible;

    }

    Login{ //Login View
        id: login
        z: 200
        visible: true
        width: mainWindow.width
        height: mainWindow.height
        anchors.horizontalCenter: mainWindow.horizontalCenter
        anchors.verticalCenter: mainWindow.verticalCenter
        onVisibleChanged: isVisible = !visible;

    }
}
