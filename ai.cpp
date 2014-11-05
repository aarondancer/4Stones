#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include <QDebug>


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

int maxAlgorithm(){
    return 0;
}

int minAlgorithm(){
    return 0;
}

int AI::makeMove(){
    switch(_difficulty){
    case 1: //Easy AI
        return minAlgorithm();
        break;
    case 2: //Medium AI
        return randomMove();
        break;
    case 3: //Hard AI
        return maxAlgorithm();
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
