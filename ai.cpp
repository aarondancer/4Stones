#include "ai.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <QDebug>

AI::AI(QObject *parent) : QObject(parent)
{
    qDebug() << "I'm an Ai";
}

void AI::makeMove(){
    switch(_difficulty){
        case 1:
            srand((unsigned)time(0));
            int random_integer;
            int lowest=0, highest=board->getGridLength() * board->getGridLength() - 1;
            int range=(highest-lowest)+1;
            random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));

            if (board->valueFromIndex(random_integer)==0){
                board->placePiece(random_integer, 2);
            }
            break;
    }
}
short AI::getDifficulty() const
{
    return _difficulty;
}

void AI::setDifficulty(short value)
{
    _difficulty = value;
}

