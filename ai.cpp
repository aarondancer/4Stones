#include "ai.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

AI::AI() : Player()
{
}

void AI::makeMove(int index){
    srand((unsigned)time(0));
    int random_integer;
    int lowest=0, highest=board->getGridLength() * board->getGridLength() - 1;
    int range=(highest-lowest)+1;
    random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));

    if (board->valueFromIndex(random_integer)==0){
        board->placePiece(random_integer, getNumber());
    }
}
