import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import com.FourStones.qmlcomponents 1.0
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 960
    title: "4Stones"

    property int turn: 1;
    property color turnColor: blue;
    property string blue: "#3359E7"
    property string red: "#FC2833"
    property color blueColor: "#3359E7"
    property color redColor: "#FC2833"
    property bool isVisible: false
    property string backgroundSource: "forest.jpg"
    property bool aiOn: false;

    property Grid board: Grid{
        id: board;
        objectName: "boardo"
        gridLength: 5;
        countToWin: 4;
    }

    property Player player: Player{
        id: player;
        objectName: "playero"
    }

    property AI computer: AI{
        id: computer
        objectName: "computero"
        difficulty: 1
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
                        color: backcolor
                        border.color: "white"
                        border.width: borderwidth
                        radius: width * 0.5
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        antialiasing: true
                        opacity: stoneopacity;
                    }

                    MouseArea { //Make the cell clickable
                        id: tileMouseArea
                        z: 1
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked:{
                            if(board.valueFromIndex(index) === 0){
                                var p = gridView.model.get(index);
                                if(turn === 1){
                                    board.placePiece(index, 1);
                                    p.backcolor = blue;
                                    p.borderwidth = 1;
                                    p.stoneopacity = 1;
                                    turn = 2;
                                    if (aiOn == true){
                                        var i = computer.makeMove();
                                        var a = gridView.model.get(i);
                                        a.backcolor = red;
                                        a.borderwidth = 1;
                                        a.stoneopacity = 1;
                                        turn = 1;
                                    }
                                }else if(turn === 2){
                                    board.placePiece(index, 2);
                                    p.backcolor = red;
                                    p.borderwidth = 1;
                                    p.stoneopacity = 1;
                                    turn = 1;
                                }
                            }
                            var check = board.checkWin(1);
                            winDialog.visible = check;
                            if (winDialog.visible === false) winDialog.visible = board.checkWin(2);
                        }
                    }
                }
            }
    }

    ListModel{
        id: gridList
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
        }
        ListElement{
            backcolor: "transparent"
            borderwidth: 0;
            stoneopacity: 0;
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
            height: mainWindow.height - 20
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.verticalCenterOffset: 200

            Row{ //This is the top quarter. Row for side-by-side layout
                id: topRow
                width: (mainWindow.height / 2 < mainWindow.width ? mainWindow.height / 2 : mainWindow.width)
                height: mainWindow.height / 4 - (undoButton.height / 4)
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



            Rectangle{ //Rectangle houses the grid, provides the outer border
                id: gridBorder
                width: (mainWindow.height / 2 < mainWindow.width ? mainWindow.height / 2 : mainWindow.width) + border.width
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
                    model: gridList
                    delegate: tileDelegate
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Text{
                id: undoButton
                text: "↩"
                height: gridView.width / 8
                font.pixelSize: height
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: (-gridView.width / 2) + (width / 2)
                MouseArea{
                    onClicked: {}
                }
            }

            Text{ //how-to text
                id: howTo
                anchors.horizontalCenter: parent.horizontalCenter
                height: Text.contentHeight
                width: gridView.width
                horizontalAlignment: Text.AlignHCenter
                text: "<html><b><u>How to play:</b></u> Players take turns placing stones. The first player to get 4 stones in a row wins!</html>"
                wrapMode: Text.WordWrap
                font.pixelSize: ((mainWindow.width > mainWindow.height)? mainWindow.height :mainWindow.width) / 32
                font.family: "Helvetica"
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
