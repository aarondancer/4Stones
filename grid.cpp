//Acts as a grid and provides the functions relating to modifying the grid
//DOES NOT provide a GUI

#include "grid.h"
#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    _lastMove = 0;
    QList<int> temp;
    for (int i = 0; i < 5; i++) temp.append(0);
    for (int j = 0; j < 5; j++) _grid.append(temp);
}

bool Grid::checkWin(int player){
    //Horizontal
    int count = 0, startR = indexToRow(_lastMove), startC = indexToColumn(_lastMove), last = _grid[startR][0];
    for (int column = 1; column < _gridLength; column++){
        if (_grid[startR][column] == last && last == player) count++;
        last = _grid[startR][column];
    }
    last = _grid[0][startC];
    if (count >= _countToWin - 1) return true;

    //Vertical
    count = 0;
    for (int row = 1; row < _gridLength; row++){
        if (_grid[row][startC] == last && last == player) count++;
        last = _grid[row][startC];
    }
    if (count >= _countToWin - 1) return true;

    // \-Diagonal
    count = 0;
    while (startR > 0 && startC > 0){
        startC--; startR--;
    }
    last = _grid[startR][startC]; startC++; startR++;
    while (startC < _gridLength && startR < _gridLength){
        if (last == _grid[startR][startC] && last == player) count++;
        last = _grid[startR][startC];
        startC++; startR++;
    }
    if (count >= _countToWin - 1) return true;

    // /-Diagonal
    count = 0;
    startR = indexToRow(_lastMove); startC = indexToColumn(_lastMove);
    while (startR > 0 && startC < _gridLength - 1){
        startR--; startC++;
    }
    //last = _grid[startR][startC]; startR++; startC--;
    while(startR < _gridLength && startC >= 0){
        if (last == _grid[startR][startC] && last == player) count++;
        last = _grid[startR][startC];
        startR++; startC--;
    }
    if (count >= _countToWin - 1) return true;

    return false;

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
    _grid[indexToRow(index)][indexToColumn(index)] = player;
}

int Grid::indexToRow(int index){
    return index / _gridLength;
}

int Grid::indexToColumn(int index){
    return index % _gridLength;
}

int Grid::coordinateToIndex(int row, int column){
    return ((row * _gridLength) + (column * _gridLength));
}

int Grid::valueFromIndex(int index){
    return _grid[indexToRow(index)][indexToColumn(index)];
}



