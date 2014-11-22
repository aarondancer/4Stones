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

int mediumAi(){    //when sum of row = 1 it will always put a stone on top left corner-----bugg

<<<<<<< Updated upstream
    int countsumrow, countsumcolumn, gridlength,holdpos, holdneg, bestcolumnvalue;
=======
<<<<<<< Updated upstream
    int countsumrow, countsumcolumn, startR, gridlength,holdpos, holdneg, bestcolumnvalue;
=======
<<<<<<< Updated upstream
    int countsumrow, countsumcolumn, startR, gridlength,holdpos, holdneg, startC, bestcolumnvalue;
=======
<<<<<<< Updated upstream
    int countsum, startR, gridlength,holdpos, holdneg, startC, bestcolumn;
=======
<<<<<<< Updated upstream
    int countsumrow, countsumcolumn, startR, gridlength,holdpos, holdneg, startC, bestcolumnvalue;
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes

    int bestcolumn, bestrow, bestrowvalue = 0;

    countsumrow, bestcolumnvalue = 0;

    gridlength = 5, holdpos = 0, holdneg = 0;

    int temp =0;

    countsumrow = 0; countsumcolumn = 0;

<<<<<<< Updated upstream
=======
   // int bestselection, bestsum =0;

   // int counter = 0;

<<<<<<< Updated upstream
    //bestrow = column, startC = 0;
=======
    bestrow = column, startC = 0;
=======
    int countsumrow, holdpos, holdneg, countcolumnsum, bestcolumn =0;

    int bestcolumnsum,column, bestdiag1,bestrow,bestrowvalue = 0;

    int gridlength=5;

    int temp =0;

>>>>>>> Stashed changes
>>>>>>> Stashed changes

>>>>>>> Stashed changes
    int array[5][5] = { {3,4,3,4,3},
                        {4,6,6,6,4},
                        {3,6,8,6,3},
                        {4,6,6,6,4},
                        {3,4,3,4,3} };


<<<<<<< HEAD
<<<<<<< Updated upstream
            for (int row = 0; row < gridlength; row++){   //counting row for best row value
=======
    for (int row = 0; row < gridlength; row++){   //counting row for best row value

        // if (countsumrow > countcolumnsum){

        if(countsumrow > holdpos){

            holdpos = countsumrow;

            if(holdpos > abs(holdneg)){

                bestrow = (row-1);

                bestrowvalue = holdpos;

            }

        }

        else if (countsumrow < holdneg){
>>>>>>> Stashed changes

            holdneg = countsumrow;

            if (abs (holdneg)>=holdpos){

                bestrow=row-1;
=======
    /* for (int r=0; r<=1;r++){
     *  for (int c=0; c<=1;c++){
     *      if (r!=1 && c!=1){
     *          int startR, startC =0;
     *          while (startR<5&&startC<5){
     *          sumdiagnal+=(board->_grid[startR][startC];
     *          startR++;
     *          startC++;
     *          }






    for (int row = 0; row < gridlength; row++){   //counting row for best row value
>>>>>>> FETCH_HEAD

                bestrowvalue = holdneg;

            }

<<<<<<< Updated upstream
                if (countsumrow >= countsumcolumn){
=======
        }
                //}

<<<<<<< Updated upstream
                if(countsum > holdpos){
=======
<<<<<<< Updated upstream
                if (countsumrow >= countsumcolumn){
>>>>>>> Stashed changes
>>>>>>> Stashed changes

                    if(countsumrow > holdpos){

                        holdpos = countsumrow;

                        if(holdpos > abs(holdneg)){

                            bestrow = (row-1);

<<<<<<< Updated upstream
                            bestrowvalue = holdpos;
=======
<<<<<<< Updated upstream
                        bestrowvalue = holdpos;
=======
<<<<<<< Updated upstream
                    bestrowvalue = holdpos;
=======
                        bestrowvalue = holdpos;
=======
              //  else{

/*
                if(countcolumnsum > holdpos){

                    holdpos = countcolumnsum;

                    if(holdpos > abs(holdneg)){

                    bestrow = (column-1);

                    bestcolumnsum = holdpos;
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes

                    }

                }

<<<<<<< Updated upstream
                    else if (countsumrow < holdneg){
=======
<<<<<<< Updated upstream
                else if (countsumrow < holdneg){
=======
<<<<<<< Updated upstream
                else if (countsum < holdneg){
=======
<<<<<<< Updated upstream
                else if (countsumrow < holdneg){
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes

                        holdneg = countsumrow;

                        if (abs(holdneg)>=holdpos){

<<<<<<< Updated upstream
                            bestrow=(row-1);
=======
<<<<<<< Updated upstream
                        bestrow=(row-1);
=======
<<<<<<< Updated upstream
                    bestrow=row;
=======
                        bestrow=(row-1);
=======
                if (countcolumnsum < holdneg){

                    holdneg = countcolumnsum;

                    if (abs (holdneg)>=holdpos){

                    bestrow=(column-1);
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes

                            bestcolumnvalue = holdneg;

                    }
                  }
                }

                else{

                    if(countsumcolumn > holdpos){

                        holdpos = countsumcolumn;

                        if(holdpos > abs(holdneg)){

                        bestcolumn = (row-1);    // find way to count column

<<<<<<< Updated upstream
                        bestcolumnvalue = holdpos;
=======
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
                        bestcolumnvalue = holdpos;
>>>>>>> Stashed changes
>>>>>>> Stashed changes

                        }

                    }

                    else if (countsumcolumn < holdneg){

                        holdneg = countsumcolumn;

                        if (abs (holdneg)>=holdpos){

                        bestcolumn=(row-1);

                        bestrowvalue = holdneg;

                        }
                    }
                }



<<<<<<< Updated upstream
                countsumrow = 0;

                countsumcolumn = 0;

                for(int column = 0;column <gridlength;column++){

                countsumrow=countsumrow+(board->_grid[row][column]);

                countsumcolumn += (board->_grid[column][row]);
=======
<<<<<<< Updated upstream
                countsum = 0;

                for(int column = 0;column <gridlength;column++){

                countsum=countsum+(board->_grid[row][column]);
=======
                countsumrow = 0;

                countsumcolumn = 0;
=======
                }

           //     }
*/
                countsumrow = 0;
                countcolumnsum =0;
>>>>>>> Stashed changes

                for(int column = 0;column <gridlength;column++){

                countsumrow=countsumrow+(board->_grid[row][column]);
<<<<<<< Updated upstream

                countsumcolumn += (board->_grid[column][row]);
>>>>>>> Stashed changes
>>>>>>> Stashed changes

=======
               // countcolumnsum+=(board->_grid[column][row]);
>>>>>>> Stashed changes

            }

           }


<<<<<<< Updated upstream

=======
<<<<<<< Updated upstream
        temp = board->coordinateToIndex(bestrow,0);
=======

<<<<<<< Updated upstream
=======


        //temp = board->coordinateToIndex(bestrow,0);
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
        if (board->getMoveCount() <=1){

       if((board->_grid[2][2])==1 || (board->_grid[2][2])==-1){

            temp = board->coordinateToIndex(3,3);
       }

       else {temp = board->coordinateToIndex(2,2);}


<<<<<<< Updated upstream
       }
=======
<<<<<<< Updated upstream
        }
=======
       }

<<<<<<< Updated upstream
        int index=0;

        if(board->getMoveCount()>1){

            if(abs(bestrowvalue)>abs(bestcolumnvalue)){

                for (int i=0;i<5;i++){

                    if ((board->_grid[bestrow][i])==0){         //this is scanning row

                        if((array[bestrow][i])>=(array[bestrow][index])){

                        temp = board->coordinateToIndex(bestrow,i);
>>>>>>> Stashed changes
>>>>>>> Stashed changes

        int index=0;

        if(board->getMoveCount()>1){

            if(abs(bestrowvalue)>=abs(bestcolumnvalue)){

                for (int i=0;i<gridlength;i++){

                    if ((board->_grid[bestrow][i])==0){         //this is scanning row

                        if((array[bestrow][i])>=(array[bestrow][index])){

                        temp = board->coordinateToIndex(bestrow,i);

                        index =i;

                        }

                    }
                }
            }
<<<<<<< Updated upstream

                else{
                    index =0;

                    for (int i=0; i<gridlength; i++){

                        if ((board->_grid[i][bestcolumn])==0){         //this is scanning row

                            if((array[i][bestcolumn])>=(array[index][bestcolumn])){

                            temp = board->coordinateToIndex(i,bestcolumn);

                            index =i;

                        }

                    }
                }

            }
       }


=======
<<<<<<< Updated upstream
        }
            }
         }
=======
       }


=======
      if (board->getMoveCount() >1){
         for (int i=0;i<5;i++){

             int index=0;

           /*  if(bestrow == 0 && bestrowvalue == 0){

                 for (int a =0; a<5;a++){
                     for (int b =0;a<5;a++){
                         if((array[bestrow][i])>=(array[bestrow][index])){

                      temp = board->coordinateToIndex(bestrow,i);

                      index =i;
                         }
                     }
                 }*/



             if ((board->_grid[bestrow][i])==0){

                        if((array[bestrow][i])>=(array[bestrow][index])){

                     temp = board->coordinateToIndex(bestrow,i);

                     index =i;
                        }

        }
            }
}
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes


       board->placePiece(temp, -1);

       return temp;

<<<<<<< Updated upstream
       qDebug() << "succesfull";
=======
       qDebug()<<board->getMoveCount();
>>>>>>> Stashed changes

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
        return randomMove();
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
