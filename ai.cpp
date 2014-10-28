#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include <QDebug>


AI::AI(QObject *parent) :
    QObject(parent)
{
}

int randomMove(){
    srand(time(NULL));
    int random_integer = rand() % 24 + 0;
    while (board->valueFromIndex(random_integer)!=0){
        random_integer = rand() % 24 + 0;
    }
    board->placePiece(random_integer, 2);
    return random_integer;
}

int AI::makeMove(){
    switch(_difficulty){
    case 1:
        return randomMove();
        break;
    case 2:
        break;
    case 3:
        break;
    default:
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
}
