#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QDebug>
#include "line.h"


AI::AI(QObject *parent) : QObject(parent) {
}

int randomMove(){
    srand(time(NULL));
    int random_integer = rand() % 24 + 0;
    while (board->valueFromIndex(random_integer)!=0){
        random_integer = rand() % 24 + 0;
    }
    board->placePiece(random_integer, -1);
    return random_integer;
}

// helper function declaration
Line bestOfLines(const Line line1, const Line line2);
int bestBlankCell(const Line &line);

int mediumAi() {
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
                if (r==1 && c==3) {
                    break;
                }
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
            for (int c = 0; c < gridlength; c++)
                currentLine.addPiece(board->_grid[r][c]);

            if (!currentLine.isFull()) // if currentLine is not full
                bestLine = bestOfLines(currentLine, bestLine); // update bestLine
        }

        // start calculating sum (or value) of vertical lines
        for (int c = 0; c < gridlength; c++) {
            currentLine.initialize(board->coordinateToIndex(0, c), vertical);
            for (int r = 0; r < gridlength; r++)
                currentLine.addPiece(board->_grid[r][c]);

            if (!currentLine.isFull()) // if currentLine is not full
                bestLine = bestOfLines(currentLine, bestLine); // update bestLine
        }

        bestMove = bestBlankCell(bestLine);
    }

    board->placePiece(bestMove, -1);
    return bestMove;
}


int maxAlgorithm(){
    return 0;
}

int minAlgorithm(){
    return 0;
}

int AI::makeMove(){
    switch(_difficulty){
    case 1: //Easy AI
        return randomMove();
        break;
    case 2: //Medium AI
        return mediumAi();
        break;
    case 3: //Hard AI
        return maxAlgorithm();
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
Line bestOfLines(Line const line1, Line const line2)
{
    Line bestLine;
    int piecesToWin = board->getCountToWin();

    srand(time(NULL)); // seed the rand() function
    bool isRandomLine = rand()  % 100 + 1 <= 50; // i.e.: 50% chance to pick line
    bool isBlocking = rand() % 100 + 1 <= 100; // i.e.: 75% chance to block


//    if ((line2.length() == 0) // line2 is zero-length
//            // or lines have the same value and is random line (chance)
//            || ((line1 == line2) && isRandomLine)
//            // or line1 is negative (i.e.: favors AI) and one piece away from winning
//            || ((line1.value() < 0) && (piecesToWin - line1.magnitude() == 1))
//            // or line1 is positive (i.e.: favors player), one piece away from winning, and is blocking (chance)
//            || ((line1.value() > 0) && (piecesToWin - line1.magnitude() == 1) && isBlocking)
//            // or line1 is more (or closer to) negative (i.e.: favors AI)
//            || (line1 < line2)
//        ) bestLine = line1;
//    else bestLine = line2;

    if (line2.length() == 0) bestLine = line1; // line2 is zero-length
    else if ((line1 == line2) && isRandomLine) bestLine = line1; // lines have the same value and is random line (chance)
    else if ((line1.value() < 0) && (piecesToWin - line1.magnitude() == 1)) bestLine = line1; // line1 is negative (i.e.: favors AI) and one piece away from winning
    else if (!((line2.value() > 0) && (piecesToWin - line2.magnitude() == 1) && isBlocking)) bestLine = line1; // line2 is positive (i.e.: favors player), one piece away from winning, and is blocking (chance)
    else if (line1 < line2) bestLine = line1; // line1 is more (or closer to) negative (i.e.: favors AI)
    else bestLine = line2;

//    int randomLine;
//
//    if (line1.length() == 0) bestLine = line2;
//    else if (line2.length() == 0) bestLine = line1;
//    else if (line1 > line2) bestLine = line1;
//    else if (line1 < line2) bestLine = line2;
//    else {
//        srand(time(NULL));
//        randomLine = rand() % 2 + 1;
//        if (randomLine == 1) bestLine = line1;
//        else bestLine = line2;
//    }

    return bestLine;
}

int bestBlankCell(const Line &line) {
    int emptyCell = -1, bestCell = -1;
    int rowOffset, colOffset;
    int row = board->indexToRow(line.startingPos());
    int col = board->indexToColumn(line.startingPos());
    int cellWeight[25] = { //cell weight used to put x and o on the grid
         3,4,3,4,3
        ,4,6,6,6,4
        ,3,6,8,6,3
        ,4,6,6,6,4
        ,3,4,3,4,3};
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
            if (bestCell == -1)
                bestCell = emptyCell;
            // wt of current emptyCell is higher than bestCell; update bestCell
            else if (cellWeight[emptyCell] > cellWeight[bestCell])
                bestCell = emptyCell;
            // wt of current emptyCell is the same as bestCell; randomly pick one to be the bestCell
            else if ((cellWeight[emptyCell] == cellWeight[bestCell]) && ((randomInt = rand() % 2) == 1))
                bestCell = emptyCell;
        }
        row += rowOffset;
        col += colOffset;
    }

    return bestCell;
}
