//Acts as a grid and provides the functions relating to modifying the grid
//DOES NOT provide a GUI

#include "grid.h"
//#include <QDebug>

Grid::Grid(QObject *parent) : QObject(parent)
{
    for (int i = 0; i < 25; i++) _grid.append(0);
}

//Win-checking algorithm. Only checks areas within range given by countToWin of the lastMove
//Completely dynamic, will work on any size grid
bool Grid::checkWin(){
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
    return false;
}

void Grid::placePiece(const int index, const int player){
    _grid.replace(index, player);
    _lastMove = index;
}
