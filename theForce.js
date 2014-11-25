function aiMove(){
    var i = computer.makeMove();
    var c = gridView.model.get(i);
    c.backcolor = red;
    c.borderwidth = 1;
    c.stoneopacity = 1;
    turn = 1;
    winDialog.visible = board.checkWin(-1);
}

function boardReset() {
    board.boardReset(); //Calls the C++ function of board to reset the 2D backend
    for (var i = 0; i < 25; i++)
        gridView.model.get(i).stoneopacity = 0; //Changes the opacity of everything on the board to 0 "Clearing" the board
}

function selectDifficulty(difficulty){
    computer.difficulty = difficulty; //Set the difficulty level of the AI
    difficultyMenu.visible = false; //Hide the difficulty selection menu
    if (difficulty === 4) aiOn = false; //If the selection was to play against friend, then turn the AI off
    goFirst.visible = true;
}

function showDifficulties(){
    login.visible = false; //Hide the login screen
    difficultyMenu.visible = true; //Show the difficulty selction menu
}

function whoGoesFirst(player){ //Sets who goes first
    turn = player;
    turnColor = (turn === -1) ? red : blue;
    goFirst.visible = false;
    if (player === -1 && aiOn === true && turn === -1) aiMove();
}

function initWhoGoesFirst(){
    firstButton.text = (player.username !== "") ? player.username : "Player 1";
    switch(computer.difficulty){
    case 1:
        secondButton.text = "Easy AI";
        break;
    case 2:
        secondButton.text = "Medium AI";
        break;
    case 3:
        secondButton.text = "Hard AI";
        break;
    case 4:
        secondButton.text = "Player 2";
    }
}

function showWinDialog(p){
    winDialog.message = "Player " + p + " wins!";
    winDialog.visible = true;
}

function showDialog(title, message, cancel, decline, accept){
    dialog.title = title;
    dialog.message = message;
    dialog.cancel = cancel;
    dialog.decline = decline;
    dialog.accept = accept;
    dialog.visible = true;
}
