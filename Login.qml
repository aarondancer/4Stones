import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import "theForce.js" as TheForce

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
        spacing: 20

        Image{ //The logo
            id: logo
            width: usernameField.width * .75
            height: width
            fillMode: Image.PreserveAspectFit
            smooth: true
            source: "4Stones.png"
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
            id: buttonRow

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
                onClicked: {player.loginPlayer(usernameField.text);}
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
                        radius: width * 0.5
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
                onClicked: {player.registerPlayer(usernameField.text);}
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
                onClicked: {TheForce.showDifficulties();}
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

    FSDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: loginSuccessDialog
        title: "Login"
        message: "Would you like to proceed and login as " + usernameField.text + "?"
        cancel: false
        accept: true
        decline: true
        visible: false
        z: 1010

        onAccepted: {
            visible = false;
            TheForce.showDifficulties();
            enable();
        }

        onDeclined: {
            visible = false;
            usernameField.text = "";
            enable();
        }

        onVisibleChanged: { menusOpen = (visible) ? menusOpen + 1 : menusOpen - 1; }
    }

    FSDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: loginFailedDialog
        title: "Login Failed"
        message: "The username " + usernameField.text + " does not exist. Please register or try again."
        cancel: true
        cancelText: "Okay"
        accept: false
        decline: false
        visible: false
        z: 1010

        onCanceled: {
            visible = false;
            enable();
        }

        onVisibleChanged: { menusOpen = (visible) ? menusOpen + 1 : menusOpen - 1; }
    }

    FSDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: registerSuccessDialog
        title: "Success!"
        message: "The username " + usernameField.text + " has been successfully registered successfully!"
        cancel: false
        accept: true
        acceptText: "Continue"
        decline: false
        visible: false
        z: 1010

        onAccepted: {
            visible = false;
            enable();
            TheForce.showDifficulties();
        }

        onVisibleChanged: { menusOpen = (visible) ? menusOpen + 1 : menusOpen - 1; }
    }

    FSDialog { //Dialog box for saying when a player has won. This will probaby be replaced eventually because ugly on mobile.
        id: registerFailedDialog
        title: "Registration Failed"
        message: "The username " + usernameField.text + " is either invalid or already taken. Please try another username or login."
        cancel: true
        cancelText: "Okay"
        accept: false
        decline: false
        visible: false
        z: 1010

        onCanceled: {
            visible = false;
            enable();
        }

        onVisibleChanged: { menusOpen = (visible) ? menusOpen + 1 : menusOpen - 1; }
    }

    function loginSuccess(){
        loginSuccessDialog.visible = true;
        disable();
    }

    function loginFailed(){
        loginFailedDialog.visible = true;
        disable();
    }

    function registerSuccess(){
        registerSuccessDialog.visible = true;
        disable();
    }

    function registerFailed(){
        registerFailedDialog.visible = true;
        disable();
    }

    function disable(){
        usernameField.enabled = false;
        loginButton.enabled = false;
        registerButton.enabled = false;
        guestButton.enabled = false;
    }

    function enable(){
        usernameField.enabled = true;
        loginButton.enabled = true;
        registerButton.enabled = true;
        guestButton.enabled = true;
    }

    function noInternet(){
        usernameField.enabled = false;
        loginButton.enabled = false;
        registerButton.enabled = false;
    }

}
