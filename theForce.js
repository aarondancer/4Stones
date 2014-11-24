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
    if (difficulty === 4) aiOn = false; //If the selection was to play against friend, then turn the AI off
}

function showDifficulties(){
    login.visible = false; //Hide the login screen
    difficultyMenu.visible = true; //Show the difficulty selction menu
}

function whoGoesFirst(player){ //Sets who goes first
    board.setFirstPlayer(player);
    initializeBoard(player);
    goFirst.visible = false;
}

function initializeBoard(firstPlayer){//Set the turn and color to correspond to "firstPlayer"
    turn = firstPlayer;
    turnColor = (turn === -1) ? red : blue;
    if (turn === -1 && aiOn === true) aiMove(); //If "firstPlayer" is AI, then AI makes first move
}
