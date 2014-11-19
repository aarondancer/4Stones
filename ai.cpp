#include "ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QDebug>


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

int mediumAi(){

    int countsum, startR, gridlength,holdpos, holdneg, startC, bestcolumn;

    int bestcolumnvalue,column, bestdiag1,bestrow,bestrowvalue = 0;

    countsum = 0; startR = 0; gridlength = 5, holdpos = 0, holdneg = 0;

    int temp =0;

    int counter = 0;

    bestrow = column, startC = 0;

    int array[5][5] = { {3,4,3,4,3},
                        {4,6,6,6,4},
                        {3,6,8,6,3},
                        {4,6,6,6,4},
                        {3,4,3,4,3} };







            for (int row = 0; row < gridlength; row++){   //counting row for best row value

                if(countsum > holdpos){

                    holdpos = countsum;

                    if(holdpos > abs(holdneg)){

                    bestrow = row;

                    bestrowvalue = holdpos;

                    }

                }

                else if (countsum < holdneg){

                    holdneg = countsum;

                    if (abs (holdneg)>=holdpos){

                    bestrow=row;

                    bestrowvalue = holdneg;

                    }



                }



                countsum = 0;

                for(int column = 0;column <gridlength;column++){

                countsum=countsum+(board->_grid[row][column]);


            }

           }


        temp = board->coordinateToIndex(bestrow,0);
        if (board->getMoveCount() <=1){

       if((board->_grid[2][2])==1 || (board->_grid[2][2])==-1){

            temp = board->coordinateToIndex(3,3);
       }

       else {temp = board->coordinateToIndex(2,2);}


        }

         int index=0;
         for (int i=0;i<5;i++){

            if ((board->_grid[2][2])==1 || (board->_grid[2][2])==-1){

                if ((board->_grid[3][3])==1 || (board->_grid[3][3])==-1){

                    if ((board->_grid[bestrow][i])==0){



                    if((array[bestrow][i])>=(array[bestrow][index])){

                    temp = board->coordinateToIndex(bestrow,i);

                    index =i;

                    }

            }
        }
            }
         }


       board->placePiece(temp, -1);

       return temp;

       qDebug()<<bestrow;

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
    qDebug() << _difficulty;
}
