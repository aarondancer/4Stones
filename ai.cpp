#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QDebug>
#include "line.h"
#include "grid.h"

#define SIZE 5
#define MAX_DEPTH 3

static unsigned int  best_move[2];
inline static int    abs_sub(int, int);
static int           negamax(int, int);

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
Line bestOfLines(const Line &line1, const Line &line2);
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

inline static int abs_sub(int minuend, int subtrahend)
{
    if(!minuend)
    {
        return 0;
    }
    return (abs(minuend) - subtrahend) * minuend/abs(minuend);
}

static int eval_grid(bool only_win) // Determines all possible moves to a specific depth
{
    int eval            = 0;
    int sum[2*SIZE+2]   = {0};
    int count[2*SIZE+2] = {0};

    for(unsigned int i=0; i<SIZE*SIZE; i++) // Generates list of possible moves
    {
        sum[i/SIZE]        += /*_grid[indexToRow(i)][indexToColumn(i)];*/board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i)));//_grid[indexToRow(i)][indexToColumn(i)];
        sum[i/SIZE+SIZE]   += /*_grid[indexToColumn(i)][indexToRow(i)];*/board->valueFromIndex(board->coordinateToIndex(board->indexToColumn(i), board->indexToRow(i)));//grid[i%SIZE][i/SIZE];
        count[i/SIZE]      += /*_grid[indexToRow(i)][indexToColumn(i)] !=0;*/board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) !=0;//grid[i/SIZE][i%SIZE] != 0;
        count[i/SIZE+SIZE] += /*_grid[indexToColumn(i)][indexToRow(i)] !=0;*/board->valueFromIndex(board->coordinateToIndex(board->indexToColumn(i), board->indexToRow(i))) !=0;//grid[i%SIZE][i/SIZE] != 0;
        //std::cout << "Check me out forreal:::::: " << _grid[indexToRow(i)][indexToColumn(i)] << "\n";
        //std::cout << "Or check me out::::::: " << board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) << "\n";

    }

    for(unsigned int i=0; i<SIZE; i++) // Evaluates individual lines
    {
        sum[2*SIZE]     += /*_grid[i][i];*/board->valueFromIndex(board->coordinateToIndex(i, i));//grid[i][i];
        count[2*SIZE]   += /*_grid[i][i] !=0;*/board->valueFromIndex(board->coordinateToIndex(i, i)) != 0;//grid[i][i] != 0;
        sum[2*SIZE+1]   += /*_grid[i][SIZE-1-i];*/board->valueFromIndex(board->coordinateToIndex(i, SIZE-1-i));//grid[i][SIZE-1-i];
        count[2*SIZE+1] += /*_grid[i][SIZE-1-i] !=0;*/board->valueFromIndex(board->coordinateToIndex(i, SIZE-1-i)) !=0;//grid[i][SIZE-1-i] != 0;
        //std::cout << "Or check me out::::::: " << board->valueFromIndex(board->coordinateToIndex(i, i)) << "\n";
    }

    for(unsigned int i=0; i<2*SIZE+2; i++) // Determines best possible score based on # of stone
    {
        if(abs(sum[i]) == 4)
        {
            if(only_win)
                return (1000 * sum[i]) / SIZE;
            eval += (1000 * sum[i]) / SIZE;
        }
        else if(only_win)
            continue;
        else if(sum[i] != 0 && abs(sum[i]) == count[i])
            eval += sum[i];
    }

    return eval;
}

static int negamax(int depth, int sign)
    {
        int max = -INT_MAX;
        //cout << "Depth = " << depth << endl;
        //int temp;//
        //int place;//

        if(depth == MAX_DEPTH)
            //return sign*abs_sub(board->checkWin(false),depth);
           return sign * abs_sub(eval_grid(false), depth);

        //cout << "abs_sub::: " << sign * abs_sub(board->eval_grid(false), depth) << endl;

        for(unsigned int i=0; i<SIZE*SIZE; i++)
        {
            int val;


            if(board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) != 0)
                continue;


           // // board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) = sign;

            board->placePiece(board->coordinateToIndex(board->indexToRow(i),board->indexToColumn(i)),sign);



            val = -negamax(depth+1, -sign);


           // // board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i)) = 0;
            board->placePiece(board->coordinateToIndex(board->indexToRow(i),board->indexToColumn(i)),0);

            std::cout << "val: " << val << "\n";
            std::cout << "max: " << max << "\n";

            if(val >= max)
            {
               if(val == max && rand()%2)
                    continue;

                max = val;
                if(depth == 0)
                {
                    //best_move[0] = ROW(i);
                    best_move[0] = board->indexToRow(i);
                    //best_move[1] = COL(i);
                    best_move[1] = board->indexToColumn(i);
                    //printf("best move is: %u:%u\n", best_move[0],
                      //      best_move[1]);
                            //std::cout << "Printing max: " << max << "\n";
                }
            }
        }


        //place = board->coordinateToIndex(board->indexToRow(best_move[0]), board->indexToColumn(best_move[1]));
        //board->placePiece(place,-1);
        //printf("best move final loop is: %u:%u\n", best_move[0], best_move[1]);

        //return max;
        //cout << "placePiece: " << place << endl;
        return max;

    }


int hardAI()
{
    unsigned int row, col, index;

           // negamax(depth, sign);
           //return negamax(0,-1);
           negamax(0,-1);
           row = best_move[0];
           col = best_move[1];
           std::cout << "ROW:::: " << row << "   COL::::" << col << "\n";
           index = board->coordinateToIndex(row,col);
           std::cout << "index::::: " << index << "\n";
           board->placePiece(index, -1);
           return index;
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

    //No winning move was found
    int medium = mediumAi(); //Run the medium AI and store value
    board->placePiece(medium, -1); //Place the medium AI move
    return medium; //Return the medium AI move
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

int bestBlankCell(const Line &line) {
    int emptyCell = -1, bestCell = -1;
    int rowOffset, colOffset;
    int row = board->indexToRow(line.startingPos());
    int col = board->indexToColumn(line.startingPos());
    int cellWeight[25] = { //cell weight used to put x and o on the grid
          3,4,3,4,3
        , 4,6,6,6,4
        , 3,6,8,6,3
        , 4,6,6,6,4
        , 3,4,3,4,3};
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
