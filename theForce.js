function aiMove(){
    var i = computer.makeMove();
    var c = gridView.model.get(i);
    c.backcolor = red;
    c.borderwidth = 1;
    c.stoneopacity = 1;
    turn = 1;
    turnColor = blue;
    winDialog.visible = board.checkWin(-1);
}

function boardReset() {//Clear the board
    board.boardReset(); //Calls the C++ function of board to reset the 2D backend
    for (var i = 0; i < 25; i++)
        gridView.model.get(i).stoneopacity = 0; //Changes the opacity of everything on the board to 0 "Clearing" the board
    initializeBoard(board.getFirstPlayer());
    mainMenu.visible = false;
}

function selectDifficulty(difficulty){
    computer.difficulty = difficulty; //Set the difficulty level of the AI
    difficultyMenu.visible = false; //Hide the difficulty selection menu
    goFirst.visible = true;
}

function showDifficulties(){
    login.visible = false; //Hide the login screen
    difficultyMenu.visible = true; //Show the difficulty selction menu
}

function whoGoesFirst(player){ //Sets who goes first
    board.setFirstPlayer(player);
    goFirst.visible = false;
    initializeBoard(player);
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

function initializeBoard(firstPlayer){//Set the turn and color to correspond to "firstPlayer"
    turn = firstPlayer;
    turnColor = (turn === -1) ? red : blue;
    if (turn === -1 && computer.difficulty !== 4) aiMove(); //If "firstPlayer" is AI, then AI makes first move
}
