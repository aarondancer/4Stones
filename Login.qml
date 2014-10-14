import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

Rectangle {
    id:loginView

    Image{ //Background, uses image for now
        id: background
        z: 0
        height: parent.height
        width: parent.width
        source: "forest.jpg"
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
        anchors.verticalCenterOffset: -logo.height / 4
        spacing: 10
        Rectangle{
            width: logo.width
            height: logo.width
            color: "transparent"
            Image{ //The logo
                id: logo
                width: usernameField.width
                height: width
                fillMode: Image.PreserveAspectFit
                smooth: true
                source: "4Stones.png"
            }
            Glow {
                   anchors.fill: logo
                   radius: 50
                   samples: 16
                   color: "white"
                   source: logo
            }
        }

        Label{
            id: usernameLabel
            text: "Enter your Username:"
            font.family: "Helvetica"
            font.weight: Font.Light
            font.pixelSize: (loginView.height < loginView.width ? loginView.height / 24 : loginView.width / 16)
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }

        TextField{
            id: usernameField
            width: usernameLabel.width
            height: usernameLabel.height
            font.pixelSize: height - 15
            font.capitalization: Font.AllUppercase
            onAccepted: {
                loginView.visible = false;
            }
        }

        Row{
            width: usernameField.width
            Button{
                text: "Login"
                width: usernameField.width / 2 - 5
                height: usernameField.height * 2
                onClicked: {loginView.visible = false;}
            }
            Rectangle{
                color: "transparent"
                width: 10
                height: 1
            }

            Button{
                text: "Play as Guest"
                width: usernameField.width / 2 - 5
                height: usernameField.height * 2
                onClicked: {loginView.visible = false;}
            }
        }
    }

}
