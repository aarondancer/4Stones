#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QDebug>
#include "line.h"
#include "grid.h"

int cellWeight[25] = { //cell weight used to put x and o on the grid
      3,4,3,4,3
    , 4,6,6,6,4
    , 3,6,8,6,3
    , 4,6,6,6,4
    , 3,4,3,4,3};

AI::AI(QObject *parent) : QObject(parent) {
}

int randomMove(){
    srand(time(NULL));
    int random_integer = rand() % 24 + 0;
    while (board->valueFromIndex(random_integer)!=0) random_integer = rand() % 24 + 0;
    board->placePiece(random_integer, -1);
    return random_integer;
}

// helper function declaration
Line bestOfLines(const Line &line1, const Line &line2);
int bestBlankCell(const Line &line, bool isHard);

int mediumAi(bool isHard) {
    Line bestLine, currentLine;
    int bestMove;
    int startR=0;
    int gridlength = board->getGridLength();
    int startC=0;

    if (board->getMoveCount() <=1) { //start of game put x/o at these coordinate
        if(board->_grid[2][2] != 0)  // center cell is occupied
            bestMove = board->coordinateToIndex(3,3);
        else bestMove = board->coordinateToIndex(2,2);
    }
    else {
        // start calculating sum (or value) of diagonal lines
        for (int r=0; r<=1;r++) {
            // start calculating sum of backward (\) diagonal lines
            for (int c=0; c<=1;c++) {
                if (r==1 && c==1) {             //breaks if come to this coordinate while in loop
                    break;
                }
                else {
                    currentLine.initialize(board->coordinateToIndex(r, c), backwardiag);
                    startR = r;
                    startC = c;

                    while ((startR < gridlength) && (startC < gridlength)) {
                        currentLine.addPiece(board->_grid[startR][startC]);
                        startR++;
                        startC++;
                    }

                    if (!currentLine.isFull()) // if currentLine is not full
                        bestLine = bestOfLines(currentLine, bestLine); // update bestLine
                }
            }

            // start calculating sum of forward (/) diagonal lines
            for (int c = 4; c >= 3; c--) {
                if (r==1 && c==3) break;
                else {
                    currentLine.initialize(board->coordinateToIndex(r, c), forwarddiag);
                    startR = r;
                    startC = c;

                    while ((startR < gridlength) && (startC >= 0)) {
                        currentLine.addPiece(board->_grid[startR][startC]);
                        startR++;
                        startC--;
                    }

                    if (!currentLine.isFull()) // if currentLine is not full
                        bestLine = bestOfLines(currentLine, bestLine); // update bestLine
                }
            }
        }

        // start calculating sum (or value) of horizontal lines
        for (int r = 0; r < gridlength; r++) {
            currentLine.initialize(board->coordinateToIndex(r, 0), horizontal);
            for (int c = 0; c < gridlength; c++) currentLine.addPiece(board->_grid[r][c]);

            if (!currentLine.isFull()) // if currentLine is not full
                bestLine = bestOfLines(currentLine, bestLine); // update bestLine
        }

        // start calculating sum (or value) of vertical lines
        for (int c = 0; c < gridlength; c++) {
            currentLine.initialize(board->coordinateToIndex(0, c), vertical);
            for (int r = 0; r < gridlength; r++) currentLine.addPiece(board->_grid[r][c]);

            if (!currentLine.isFull()) // if currentLine is not full
                bestLine = bestOfLines(currentLine, bestLine); // update bestLine
        }

        bestMove = bestBlankCell(bestLine, isHard);
    }

    board->placePiece(bestMove, -1);
    return bestMove;
}

int smartAI(){
    Grid tempboard; //Create a temp grid
    tempboard._gridLength = 5;
    tempboard._countToWin = 4;

    //Clone the board to the temp grid
    for (int i = 0; i < board->_gridLength * board->_gridLength; i++)
        tempboard._grid[tempboard.indexToRow(i)][tempboard.indexToColumn(i)] = board->valueFromIndex(i);

    //Loop through board to check if there is a possible win
    for (int j = 0; j < tempboard._gridLength * tempboard._gridLength; j++){
        int old = tempboard.valueFromIndex(j);
        if (old == 0){
            tempboard.placePiece(j, -1);
            if (tempboard.checkWin(-1)) { //If there's a possible win, place it on the board and return that position
                board->placePiece(j, -1);
                return j;
            }
            tempboard.placePiece(j, old); //If not, removed that piece from the temp board
        }
    }

    for (int j = 0; j < tempboard._gridLength * tempboard._gridLength; j++){ //For some reason this really only works if I make a totally separate loop
        int old = tempboard.valueFromIndex(j);
        if (old == 0){
            tempboard.placePiece(j, 1);
            if (tempboard.checkWin(1)) { //If there's a possible win, place it on the board and return that position
                board->placePiece(j, -1);
                return j;
            }
            tempboard.placePiece(j, old); //If not, removed that piece from the temp board
        }
    }

    for (int x = -1; x <= 1; x++){
        if (abs(x) == 1){
            //Find fork
            //Horizontal
            for (int k = 0; k <=20; k+= 5){
                if (tempboard.valueFromIndex(k) == 0 && tempboard.valueFromIndex(k + 4) == 0){
                    int count = 0;
                    for (int l = k + 1; l <= k + 3; l++) if (tempboard.valueFromIndex(l) == x) count++;
                    if (count == 2) for (int l = k + 1; l <= k + 3; l++){
                        if (tempboard.valueFromIndex(l) == 0){
                            board->placePiece(l, -1);
                            return l;
                        }
                    }

                }
            }

            //Vertical
            for (int k = 0; k <=4; k++){
                if (tempboard.valueFromIndex(k) == 0 && tempboard.valueFromIndex(k + 20) == 0){
                    int count = 0;
                    for (int l = k + 5; l <= k + 15; l+=5) if (tempboard.valueFromIndex(l) == x) count++;
                    if (count == 2) for (int l = k + 5; l <= k + 15; l+=5){
                        if (tempboard.valueFromIndex(l) == 0){
                            board->placePiece(l, -1);
                            return l;
                        }
                    }

                }
            }

            //\Diagonal
            if (tempboard.valueFromIndex(0) == 0 && tempboard.valueFromIndex(24) == 0){
                int count = 0;
                for (int l = 6; l <= 18; l+=6) if (tempboard.valueFromIndex(l) == x) count++;
                if (count == 2) for (int l = 6; l <= 18; l+=6){
                    if (tempboard.valueFromIndex(l) == 0){
                        board->placePiece(l, -1);
                        return l;
                    }
                }
            }

            ///Diagonal
            if (tempboard.valueFromIndex(4) == 0 && tempboard.valueFromIndex(20) == 0){
                int count = 0;
                for (int l = 8; l <= 16; l+=4) if (tempboard.valueFromIndex(l) == x) count++;
                if (count == 2) for (int l = 8; l <= 16; l+=4){
                    if (tempboard.valueFromIndex(l) == 0){
                        board->placePiece(l, -1);
                        return l;
                    }
                }
            }
        }else{
            int steps [8][3] = {{0, 4, 1}, //Horizontal //0
                                {0, 20, 5}, //Vertical  //1
                                {0, 24, 6}, // \ Diags  //2
                                {1, 19, 6},             //3
                                {5, 23, 6},             //4
                                {3, 15, 4}, // /Diags   //5
                                {4, 20, 4},             //6
                                {9, 21, 4}};            //7

            for(int i = 0; i < 8; i++){ //Horizontal and Vertical
                if (i < 2){
                    int val1 = (i == 0) ? 21 : 5;
                    int val2 = (i == 0) ? 5 : 1;
                    for (int k = 0; k < val1; k+= val2){ //Loop through rows or columns
                        QList<int> l; //Holds the 1D indexes of that line
                        QList<int> v; //Holds the values of that line
                        for (int z = 0; z < 5; z++) { l.append(0); v.append(0); }
                        int looped = 0; //Keep track of how many times the loop has looped
                        for (int j = steps[i][0] + k; j <= steps[i][1] + k; j+= steps[i][2]){ //Iterate through every space in that line and store it into l and v
                            l[looped] = j;
                            v[looped] = tempboard.valueFromIndex(j);
                            looped++;
                        }
                        for (int a = 0; a < 2; a++){ //Stagger checks
                            if (v[0 + a] == -1 && v[1 + a] == 0 && v[2 + a] == -1 && v[3 + a] == 0) board->placePiece(l[1 + a], -1);
                            else if (v[0 + a] == -1 && v[1 + a] == -1 && v[2 + a] == 0 && v[3 + a] == 0) board->placePiece(l[2 + a], -1);
                            else if (v[0 + a] == 0 && v[1 + a] == -1 && v[2 + a] == 0 && v[3 + a] == -1) board->placePiece(l[2 + a], -1);
                            else if (v[0 + a] == 0 && v[1 + a] == 0 && v[2 + a] == -1 && v[3 + a] == -1) board->placePiece(l[1 + a], -1);
                            else if (v[0 + a] == 0 && v[1 + a] == -1 && v[2 + a] == -1 && v[3 + a] == 0)
                                board->placePiece(l[(cellWeight[l[0 + a]] > cellWeight[l[3 + a]]) ? l[0 + a] : l[3 + a]], -1);
                        }

                        if (board->valueFromIndex(board->_lastMove) == -1) return board->_lastMove;
                    }
                }/*else if (i != 4 && i != 5) { //4 is bugged for some reason
                    QList<int> l; //Holds the 1D indexes of that line
                    QList<int> v; //Holds the values of that line
                    for (int z = 0; z < 4; z++) { l.append(0); v.append(0); }
                    int looped = 0; //Keep track of how many times the loop has looped
                    for (int j = steps[i][0]; j <= steps[i][1]; j+= steps[i][2]){ //Iterate through every space in that line and store it into l and v
                        l[looped] = j;
                        v[looped] = tempboard.valueFromIndex(j);
                        looped++;
                    }
//                    qDebug() << l;
//                    qDebug() << v;
                    if (v[0] == -1 && v[1] == 0 && v[2] == -1 && v[3] == 0) board->placePiece(l[1], -1);
                    else if (v[0] == -1 && v[1] == -1 && v[2] == 0 && v[3] == 0) board->placePiece(l[2], -1);
                    else if (v[0] == 0 && v[1] == -1 && v[2] == 0 && v[3] == -1) board->placePiece(l[2], -1);
                    else if (v[0] == 0 && v[1] == 0 && v[2] == -1 && v[3] == -1) board->placePiece(l[1], -1);
                    else if (v[0] == 0 && v[1] == -1 && v[2] == -1 && v[3] == 0)
                        board->placePiece(l[(cellWeight[l[0]] > cellWeight[l[3]]) ? l[0] : l[3]], -1);

                    if (board->valueFromIndex(board->_lastMove) == -1) return board->_lastMove;
                }*/
            }
        }
    }

    //No winning move was found
    int medium = mediumAi(true); //Run the medium AI and store value
    board->placePiece(medium, -1); //Place the medium AI move
    return medium; //Return the medium AI move
}

int AI::makeMove(){
    switch(_difficulty){
    case 1: //Easy AI
        return randomMove();
        break;
    case 2: //Medium AI
        return mediumAi(false);
        break;
    case 3: //Hard AI
        return smartAI();
        break;

    default:
        return randomMove();
        break;
    }
}

int AI::getDifficulty() const
{
    return _difficulty;
}

void AI::setDifficulty(int value)
{
    _difficulty = value;
    qDebug() << "Difficulty setting:" << _difficulty;
}

// helper functions
int forkPreventer(){
    int bestCell = 100;
    if (board->_grid[2][2] == 1 &&
            board->_grid[2][3] == 1 &&
            board->_grid[1][2] == 1 &&
            board->_grid[1][3] == 1 &&
            board->valueFromIndex(16) == 0){
        bestCell = 16;
    } else if (board->_grid[2][2] == 1 &&
               board->_grid[2][1] == 1 &&
               board->_grid[3][2] == 1 &&
               board->_grid[3][1] == 1 &&
               board->valueFromIndex(8) == 0
               ){
        bestCell = 8;
    } else if (board->_grid[1][1] == 1 &&
               board->_grid[2][1] == 1 &&
               board->_grid[2][2] == 1 &&
               board->valueFromIndex(13) == 0
               ){
        bestCell = 13;
    } else if (board->_grid[2][2] == 1 &&
               board->_grid[2][1] == 1 &&
               board->_grid[3][1] == 1 &&
               board->valueFromIndex(8) == 0
               ){
        bestCell = 8;
    } else if (board->_grid[1][1] == 1 &&
               board->_grid[2][1] == 1 &&
               board->_grid[1][2] == 1 &&
               board->valueFromIndex(8) == 0
               ){
        bestCell = 8;
    } else if (board->_grid[1][2] == 1 &&
               board->_grid[2][2] == 1 &&
               board->_grid[1][3] == 1 &&
               board->valueFromIndex(16) == 0
               ){
        bestCell = 16;
    } else if (board->_grid[0][1] == 1 &&
              board->_grid[1][1] == 1 &&
              board->_grid[1][2] == 1 &&
              board->_grid[2][1] == 1 &&
              board->valueFromIndex(16) == 0
              ){
       bestCell = 16;
    }
    else if (board->_grid[0][1] == 1 &&
              board->_grid[1][2] == 1 &&
              board->_grid[2][1] == 1 &&
              board->valueFromIndex(6) == 0
              ){
       bestCell = 6;
    }

    else if (board->_grid[1][2] == 1 &&
              board->_grid[2][1] == 1 &&
              board->_grid[3][2] == 1 &&
              board->valueFromIndex(1) == 0
              ){
       bestCell = 1;
    }

    else if (board->_grid[2][1] == 1 &&
              board->_grid[2][2] == 1 &&
              board->_grid[3][2] == 1 &&
              board->_grid[1][3] == 1 &&
              board->valueFromIndex(16) == 0
              ){
       bestCell = 16;
    }

    else if (board->_grid[3][1] == 1 &&
              board->_grid[2][2] == 1 &&
              board->_grid[3][2] == 1 &&
              board->_grid[2][3] == 1 &&
              board->valueFromIndex(8) == 0
              ){
       bestCell = 8;
    }

    else if (board->_grid[1][3] == 1 &&
              board->_grid[2][2] == 1 &&
              board->_grid[3][2] == 1 &&
              board->_grid[2][3] == 1 &&
              board->valueFromIndex(16) == 0
              ){
       bestCell = 16;
    }
    return bestCell;
}

Line bestOfLines(const Line &line1, const Line &line2)
{
    Line bestLine;
   // int randomLine;

    if (line1.length() == 0) bestLine = line2;
    else if (line2.length() == 0) bestLine = line1;
    else if (line1 > line2) bestLine = line1;
    else if (line1 < line2) bestLine = line2;
    else if (line1==line2)bestLine=line1;
//    else {
//        srand(time(NULL));
//        randomLine = rand() % 2 + 1;
//        if (randomLine == 1) bestLine = line1;
//        else bestLine = line2;
//    }

    return bestLine;
}

int bestBlankCell(const Line &line, bool isHard) {
    int emptyCell = -1, bestCell = -1;
    int rowOffset, colOffset;
    int row = board->indexToRow(line.startingPos());
    int col = board->indexToColumn(line.startingPos());
    int randomInt;

    srand(time(NULL));

    switch (line.direction()) {
        case Direction::horizontal:
            rowOffset = 0;
            colOffset = 1;
            break;
        case Direction::vertical:
            rowOffset = 1;
            colOffset = 0;
            break;
        case Direction::backwardiag:
            rowOffset = 1;
            colOffset = 1;
            break;
        case Direction::forwarddiag:
            rowOffset = 1;
            colOffset = -1;
            break;
        default:
            break;
    }

    for(int i = 0; i < line.length(); i++) {

        if (board->_grid[row][col] == 0) {
            emptyCell = board->coordinateToIndex(row, col);

            // bestCell has not been set; update bestCell
            if (bestCell == -1) bestCell = emptyCell;
            // wt of current emptyCell is higher than bestCell; update bestCell
            else if (cellWeight[emptyCell] > cellWeight[bestCell]) bestCell = emptyCell;
            // wt of current emptyCell is the same as bestCell; randomly pick one to be the bestCell
            else if ((cellWeight[emptyCell] == cellWeight[bestCell]) && ((randomInt = rand() % 2) == 1))
                bestCell = emptyCell;
        }
        row += rowOffset;
        col += colOffset;
    }

    if (isHard){ //Hard coding some solutions to forks
        int forkvar = forkPreventer();
        if (forkvar != 100) bestCell = forkvar;
    }

    return bestCell;
}
