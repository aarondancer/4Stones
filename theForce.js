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
}

function showDifficulties(){
    login.visible = false; //Hide the login screen
    difficultyMenu.visible = true; //Show the difficulty selction menu
}

function whoGoesFirst(player){ //Sets who goes first
    turn = player;
    turnColor = (turn === -1) ? red : blue;
    goFirst.visible = false;
    if (player === -1) aiMove();
}
