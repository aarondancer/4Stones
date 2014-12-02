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
 int           negamax(int *iBoard, int, int);

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
int bestBlankCell(const Line &line, bool isHard);
int eval_position(int iBoard[], int player);
void cloneBoard(int iBoard[], int clone[]);
void cloneBoard(Grid *grid, int clone[]);

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

        bestMove = bestBlankCell(bestLine, isHard);
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

//static int eval_grid(bool only_win) // Determines all possible moves to a specific depth
//{
//    int eval            = 0;
//    int sum[2*SIZE+2]   = {0};
//    int count[2*SIZE+2] = {0};

//    for(unsigned int i=0; i<SIZE*SIZE; i++) // Generates list of possible moves
//    {
//        sum[i/SIZE]        += /*_grid[indexToRow(i)][indexToColumn(i)];*/board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i)));//_grid[indexToRow(i)][indexToColumn(i)];
//        sum[i/SIZE+SIZE]   += /*_grid[indexToColumn(i)][indexToRow(i)];*/board->valueFromIndex(board->coordinateToIndex(board->indexToColumn(i), board->indexToRow(i)));//grid[i%SIZE][i/SIZE];
//        count[i/SIZE]      += /*_grid[indexToRow(i)][indexToColumn(i)] !=0;*/board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) !=0;//grid[i/SIZE][i%SIZE] != 0;
//        count[i/SIZE+SIZE] += /*_grid[indexToColumn(i)][indexToRow(i)] !=0;*/board->valueFromIndex(board->coordinateToIndex(board->indexToColumn(i), board->indexToRow(i))) !=0;//grid[i%SIZE][i/SIZE] != 0;
//        //std::cout << "Check me out forreal:::::: " << _grid[indexToRow(i)][indexToColumn(i)] << "\n";
//        //std::cout << "Or check me out::::::: " << board->valueFromIndex(board->coordinateToIndex(board->indexToRow(i), board->indexToColumn(i))) << "\n";

//    }

//    for(unsigned int i=0; i<SIZE; i++) // Evaluates individual lines
//    {
//        sum[2*SIZE]     += /*_grid[i][i];*/board->valueFromIndex(board->coordinateToIndex(i, i));//grid[i][i];
//        count[2*SIZE]   += /*_grid[i][i] !=0;*/board->valueFromIndex(board->coordinateToIndex(i, i)) != 0;//grid[i][i] != 0;
//        sum[2*SIZE+1]   += /*_grid[i][SIZE-1-i];*/board->valueFromIndex(board->coordinateToIndex(i, SIZE-1-i));//grid[i][SIZE-1-i];
//        count[2*SIZE+1] += /*_grid[i][SIZE-1-i] !=0;*/board->valueFromIndex(board->coordinateToIndex(i, SIZE-1-i)) !=0;//grid[i][SIZE-1-i] != 0;
//        //std::cout << "Or check me out::::::: " << board->valueFromIndex(board->coordinateToIndex(i, i)) << "\n";
//    }

//    for(unsigned int i=0; i<2*SIZE+2; i++) // Determines best possible score based on # of stone
//    {
//        if(abs(sum[i]) == 4)
//        {
//            if(only_win)
//                return (1000 * sum[i]) / SIZE;
//            eval += (1000 * sum[i]) / SIZE;
//        }
//        else if(only_win)
//            continue;
//        else if(sum[i] != 0 && abs(sum[i]) == count[i])
//            eval += sum[i];
//    }

//    return eval;
//}

// ///////////////////
void cloneBoard(int boardToClone[], int clone[])
{
    //int clone[25];

    for(int j = 0 ; j < 25; j++)
    {
        clone[j] = boardToClone[j];
    }

}

void cloneBoard(Grid *grid, int clone[])
{
    for(int j = 0 ; j < 25; j++)
    {
        clone[j] = grid->valueFromIndex(j);
    }
}

#define Possible_Wins 28

const int Heuristic_Array[5][5] =
{
    {0, -10, -100, -1000, -10000},
    {10, 0, -10, -100, -1000},
    {100, 10, 0, -10, -100},
    {1000, 100, 10, 0, -10},
    {10000, 1000, 100, 10, 0}
};

//const int Heuristic_Array[5][5] =
//{
//    {0, -10, -100, -1000, -10000},
//    {10, 0, 0, 0, 0},
//    {100, 0, 0, 0, 0},
//    {1000, 0, 0, 0, 0},
//    {10000, 0, 0, 0, 0}
//};
//const int Heuristic_Array[5][5] =
//{
//    {0, 10, 100, 1000, 10000},
//    {-10, 0, 10, 100, 1000},
//    {-100, -10, 0, 10, 100},
//    {-1000, -100, -10, 0, 10},
//    {-10000, -1000, -100, -10, 0}
//};

//const int Heuristic_Array[5][5] =
//{
//    {0, 10, 100, 1000, 10000},
//    {100000, 0, 10, 100, 1000},
//    {1000000, 100000, 0, 10, 100},
//    {10000000, 1000000, 100000, 0, 10},
//    {100000000, 10000000, 1000000, 100000, 0}
//};

const int Four_in_a_Row[Possible_Wins][4] =
{
    {0,1,2,3},
    {1,2,3,4},
    {5,6,7,8},
    {6,7,8,9},
    {10,11,12,13},
    {11,12,13,14},
    {15,16,17,18},
    {16,17,18,19},
    {20,21,22,23},
    {21,22,23,24},
    {0,5,10,15},
    {5,10,15,20},
    {1,6,11,16},
    {6,11,16,21},
    {2,7,12,17},
    {7,12,17,22},
    {3,8,13,18},
    {8,13,18,23},
    {4,9,14,19},
    {9,14,19,24},
    {0,6,12,18},
    {6,12,18,24},
    {1,7,13,19},
    {5,11,17,23},
    {4,8,12,16},
    {8,12,16,20},
    {3,7,11,15},
    {9,13,17,21}
};

//static int eval_grid(int grid[25])
//{
//    int gridLength = board->getGridLength();
//    int gridValue = 0;

//    bool isPossibleMove[25] = false;
//    for(int i = 0; i < gridLength; i++)
//    {
//        if(board->valueFromIndex(i) == 0)
//        {
//            isPossibleMove[i] = true;
//        }
//    }

//    int tempBoard[25];

//    for(int i = 0; i < gridLength; i++)
//    {
//        if(isPossibleMove[i])
//        {
////            for(j = 0 ; j < gridLength; j++)
////            {
////                tempBoard[j] = board->valueFromIndex(j);
////            }
//            cloneBoard(grid, tempBoard);

//            tempBoard[i] = -1;

//            gridValue = eval_position(tempBoard, -1);

//            int tempBoardValue = gridValue;
//            if ()
//        }
//    }

//    return gridValue;
//}


int eval_position(int *board, int player)
{
    int opponent = (player == 1) ? -1 : 1;
    int stone;
    int playerStones, opponentStones;
    int val = 0;
    int heuristicVal = 0;

    for(int i = 0; i < 28; i++)
    {
        playerStones = opponentStones = 0;

        for(int j = 0; j < 4; j++)
        {
            stone = board[Four_in_a_Row[i][j]];
            if (stone == player)
            {
                playerStones++;
            }
            else if(stone == opponent)
            {
                opponentStones++;
            }
        }
        heuristicVal = Heuristic_Array[playerStones][opponentStones];
        val += heuristicVal;
    }

    return val;

}

int negamax(int *iBoard, int depth, int sign)
{
    int max = -INT_MAX;
    int val;
    int bestValue = max;
    int piece;

    if(depth == 0)
        return sign * eval_position(iBoard, sign);
    else
        for(unsigned int i=0; i<25; i++)
        {
            int tempBoard[25] = {0};

            piece = iBoard[i];
            if(piece == 0)
            {
                cloneBoard(iBoard,tempBoard);
                tempBoard[i] = sign;
                val = -negamax(tempBoard, depth-1, -sign);
                // possible undo
                tempBoard[i] = 0;
                if(val > bestValue)
                {
                    bestValue = val;
                }
             }
        }
    return bestValue;
}


int hardAI()
{
    int max = -INT_MAX;
    int val;
    int bestValue = max;
    int bestMove = -1;
    int sign = -1;
    int piece;

    for(int i=0; i<SIZE*SIZE; i++)
    {
        int tempBoard[25] = {0};
        int depth = MAX_DEPTH;

        piece = board->valueFromIndex(i);

        if(piece == 0)
        {
            cloneBoard(board,tempBoard);
            tempBoard[i] = sign;
            val = negamax(tempBoard, depth, -sign);
            // possible undo
//            tempBoard[i] = 0;
            if(val > bestValue || bestMove == -1)
            {
                bestValue = val;
                bestMove = i;
            }
         }
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
        //return smartAI();
        return hardAI();
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

    if (isHard){ //Hard coding some solutions to forks
        int forkvar = forkPreventer();
        if (forkvar != 100) bestCell = forkvar;
    }

    return bestCell;
}
