import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2

Rectangle {
    id:loginView

    Image{ //Background, uses image for now
        id: loginBackground
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

    Column{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -logo.height / 4
        spacing: 20
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
                   anchors.fill: parent
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
            height: usernameLabel.height + 10
            font.pixelSize: height - 15
            font.capitalization: Font.AllUppercase
            onAccepted: {
                loginView.visible = false;
            }

            style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 0
                        border.color: "#333"
                        border.width: 1
                    }
                }
        }

        Row{
            anchors.horizontalCenter: usernameField.horizontalCenter
            width: usernameField.width
            height : usernameField.height * 2

            Rectangle{
                color: "transparent"
                width: (usernameField.width - (loginButton.width * 3) - 20) / 2
                height: 1
            }

            Button{
                id: loginButton
                text: "Login"
                width: height
                height: usernameField.height * 2
                onClicked: {loginView.visible = false;}
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
                            color: (control.hovered) ? blue : Qt.lighter(blue, 1.2)
                    }
                }
            }
            Rectangle{
                color: "transparent"
                width: 10
                height: 1
            }

            Button{
                id: registerButton
                text: "Register"
                width: height
                height: usernameField.height * 2
                onClicked: {loginView.visible = false;}
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
                        color: (control.hovered) ? red : Qt.lighter(red, 1.2)
                    }
                }

            }

            Rectangle{
                color: "transparent"
                width: 10
                height: 1
            }

            Button{
                id: guestButton
                text: "Play as Guest"
                width: height
                height: usernameField.height * 2
                onClicked: {loginView.visible = false;}
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
                        color: (control.hovered) ? "grey" : Qt.lighter("grey", 1.2)
                    }
                }
            }
        }
    }

}
