//Acts as a grid and provides the functions relating to modifying the grid
//DOES NOT provide a GUI

#include "grid.h"
#include <QDebug>
#include "iostream"
#include "string"

#define SIZE 5

Grid::Grid(QObject *parent) : QObject(parent)
{
    _lastMove = 0;
    _moveCount = 0;
    QList<int> temp;
    for (int i = 0; i < 5; i++) temp.append(0);
    for (int j = 0; j < 5; j++) _grid.append(temp);
}

bool Grid::isFilled(){
    return (_moveCount == 25);
}

bool Grid::checkWin(int player){
    bool isWin = false;
    int count, startR, startC, last;

    //Horizontal
    if (!isWin) {

        count = 0; startR = indexToRow(_lastMove); startC = 0; last = _grid[startR][startC];
        for (int column = 1; column < _gridLength; column++){
            if (_grid[startR][column] == last && last == player) count++;
            last = _grid[startR][column];
         // std::cout << "Horizontal check win player " << player << "\n"<< "last"<< last << "\n";
        }
        isWin = (count >= _countToWin - 1);
        if (isWin) qDebug() << "Horizontal win";

    }

    //Vertical
    if (!isWin) {
        count = 0; startR = 0; startC = indexToColumn(_lastMove); last = _grid[startR][startC];
        for (int row = 1; row < _gridLength; row++){
            if (_grid[row][startC] == last && last == player) count++;
            last = _grid[row][startC];
                  // std::cout << "Vertical check win player " << player << "\n"<< "last"<< last << "\n";
        }
        isWin = (count >= _countToWin - 1);
        if (isWin) qDebug() << "Vertical win";
    }

    // \-Diagonal
    if (!isWin) {
        count = 0; startR = indexToRow(_lastMove); startC = indexToColumn(_lastMove);
        while (startR > 0 && startC > 0) {
            startR--; startC--; // move to start of diagonal; i.e.: upper-left-most cell
        }
        last = _grid[startR][startC]; startR++; startC++;
        while (startC < _gridLength && startR < _gridLength){
            if (_grid[startR][startC] == last && last == player) count++;
            last = _grid[startR][startC];
            startR++; startC++;
        }
        isWin = (count >= _countToWin - 1);
        if (isWin) qDebug() << "\\-Diag win";
               //std::cout << "diag\ check win player " << player << "\n"<< "last"<< last << "\n";
    }

    // /-Diagonal
    if (!isWin) {
        count = 0; startR = indexToRow(_lastMove); startC = indexToColumn(_lastMove);
        while (startR > 0 && startC < _gridLength - 1) {
            startR--; startC++; // move to start of diagonal; i.e.: upper-right-most cell
        }
        last = _grid[startR][startC]; startR++; startC--;
        while(startR < _gridLength && startC >= 0){
            if (_grid[startR][startC] == last && last == player) count++;
            last = _grid[startR][startC];
            startR++; startC--;
        }
        isWin = (count >= _countToWin - 1);
        if (isWin) qDebug() << "/-Diag win";
               //std::cout << "diag/ check win player " << player << "\n"<< "last"<< last << "\n";
    }

    return isWin;

    /*//Old 1D Algorithm
    const int steps[4] = {1, _gridLength, _gridLength + 1, _gridLength - 1}; //1 = Horizontal, _gridLength = Vertical, + 1 = Diagonal L->R, - 1 = Diagonal R->L
    for (int step = 0; step < 4; step++){
        //Set the grid limits
        int vLimit = (_gridLength * (_gridLength - 1)) + (_lastMove % steps[step]);
        int hLimit = (((_lastMove / _gridLength) + 1) * _gridLength) - 1;
        int dLRLimit = (_gridLength - 1) * steps[step];
        int start, end, count = 0, gridArea = _gridLength * _gridLength;

        if (_lastMove > 0 && _lastMove < gridArea) start = _lastMove - ((_countToWin - 1) * steps[step]);
        else start = _lastMove;
        while (start < 0) start += steps[step];

        end = _lastMove + ((_countToWin - 1) * steps[step]);
        while (end > (gridArea) - 1) end -= steps[step];
        if (steps[step] == 1 && end > hLimit) end = hLimit;
        if (steps[step] == _gridLength && end > vLimit) end = vLimit;
        if (steps[step] == steps[2] && end > dLRLimit) end = dLRLimit;
        if (steps[step] == steps[3]) while (end > (gridArea) - _countToWin) end -= steps[step];

        for (int c = start; c < end; c+=steps[step]) if(c+steps[step]<gridArea) if (_grid[c]==_grid[c+steps[step]] && _grid[c] == _grid[_lastMove]) count++;
        if (count==_countToWin - 1) return true;
    }
    return false;*/
}

void Grid::placePiece(const int index, const int player){
    _lastMove = index;
    _moveCount++;
    if (player == 1) _lastMoveX = _lastMove;
    else _lastMoveO = _lastMove;
    _grid[indexToRow(index)][indexToColumn(index)] = player;
}

int Grid::indexToRow(int index){
    return index / _gridLength;
}

int Grid::indexToColumn(int index){
    return index % _gridLength;
}

int Grid::coordinateToIndex(int row, int column){
    return ((row * _gridLength) + column);
}

int Grid::valueFromIndex(int index){
    return _grid[indexToRow(index)][indexToColumn(index)];
}

int Grid::lastMoveX() const
{
    return _lastMoveX;
}

void Grid::setLastMoveX(int lastMoveX)
{
    _lastMoveX = lastMoveX;
}
int Grid::lastMoveO() const
{
    return _lastMoveO;
}

void Grid::setlastMoveO(int lastMoveO)
{
    _lastMoveO = lastMoveO;
}

void Grid::boardReset(){
    _lastMove = 0;
    _moveCount = 0; // reset move counter
    for(int i = 0; i < (_gridLength * _gridLength); i++) {
        //placePiece(i, 0); // replaced with statement below b/c placePiece() has additional logic that is not necessary for this funtion
        _grid[indexToRow(i)][indexToColumn(i)] = 0;
    }
    qDebug() << "Board Reset.  First player: " << _firstPlayer;
}

int Grid::getFirstPlayer() const {
    return _firstPlayer;
}

void Grid::setFirstPlayer(int player) {
    _firstPlayer = player;
    qDebug() << "First player set: " << _firstPlayer;
}

bool Grid::moveIsValid(int index)//Check me out
{
    //if(valueFromIndex(index) == 1 || valueFromIndex(index) == -1)
    if(valueFromIndex(index) == 0)
        return true;
    else return false;
}

/*int Grid::eval_grid(bool only_win)
{
    int eval            = 0;
    int sum[2*SIZE+2]   = {0};
    int count[2*SIZE+2] = {0};

    for(unsigned int i=0; i<SIZE*SIZE; i++)
    {
        sum[i/SIZE]        += _grid[indexToRow(i)][indexToColumn(i)];//valueFromIndex(coordinateToIndex(indexToRow(i), indexToColumn(i)));//_grid[indexToRow(i)][indexToColumn(i)];
        sum[i/SIZE+SIZE]   += _grid[indexToColumn(i)][indexToRow(i)];//valueFromIndex(coordinateToIndex(indexToColumn(i), indexToRow(i)));//grid[i%SIZE][i/SIZE];
        count[i/SIZE]      += _grid[indexToRow(i)][indexToColumn(i)] !=0;//valueFromIndex(coordinateToIndex(indexToRow(i), indexToColumn(i))) !=0;//grid[i/SIZE][i%SIZE] != 0;
        count[i/SIZE+SIZE] += _grid[indexToColumn(i)][indexToRow(i)] !=0;//valueFromIndex(coordinateToIndex(indexToColumn(i), indexToRow(i))) !=0;//grid[i%SIZE][i/SIZE] != 0;
        std::cout << "Check me out forreal:::::: " << _grid[indexToRow(i)][indexToColumn(i)] << "\n";
        //std::cout << "Or check me out::::::: " << valueFromIndex(coordinateToIndex(indexToRow(i), indexToColumn(i))) << "\n";

    }

    for(unsigned int i=0; i<SIZE; i++)
    {
        sum[2*SIZE]     += _grid[i][i];//valueFromIndex(coordinateToIndex(i, i));//grid[i][i];
        count[2*SIZE]   += _grid[i][i] !=0;//valueFromIndex(coordinateToIndex(i, i)) != 0;//grid[i][i] != 0;
        sum[2*SIZE+1]   += _grid[i][SIZE-1-i];//valueFromIndex(coordinateToIndex(i, SIZE-1-i));//grid[i][SIZE-1-i];
        count[2*SIZE+1] += _grid[i][SIZE-1-i] !=0;//valueFromIndex(coordinateToIndex(i, SIZE-1-i)) !=0;//grid[i][SIZE-1-i] != 0;
    }

    for(unsigned int i=0; i<5*SIZE+5; i++) //Affects the number of X or O's to win
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
}*/

