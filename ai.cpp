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

int mediumAi() {
    int countsumrow=0;                          // declare local variable to be used
    int countsumcolumn=0;
    int startR=0;
    int bestdiagoverall=0;
    int diagnacoor=0;
    int gridlength=5;
    int holdpos=0;
    int holdneg=0;
    int startC=0;
    int bestcolumnvalue=0;
    int bestcolumn=0;
    int bestrow = 0;
    int bestrowvalue = 0;
    int countsumdiagnal =0;
    int temp =0;
    int bestdiagnal1value=0;
    int bestdiagnal2value=0;
    int bestdiagnal3value=0;
    int bestdiagnal4value=0;
    int bestdiagnal5value=0;
    int bestdiagnal6value=0;
    int array[5][5] = { {                   //array weight used to put x and o on the grid base on score
            3,4,3,4,3
        }
        , {
            4,6,6,6,4
        }
        , {
            3,6,8,6,3
        }
        , {
            4,6,6,6,4
        }
        , {
            3,4,3,4,3
        }
    }
    ;
    for (int r=0; r<=1;r++) {               //start of calculating sum of diagnally
        for (int c=0; c<=1;c++) {
            countsumdiagnal = 0;
            if (r==1 && c==1) {             //breaks if come to this coordinate while in loop
                break;
            }
            else {
                startR=r;
                startC =c;
                if ((r==0)&&(c==0)) {       //sum of diagnal 1
                    while ((startR<5)&&(startC<5)) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC++;
                    }
                } else if ((r==0)&&(c==1)) {        //sum of diagnal 2
                    while (startR<4&&startC<5) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC++;
                    }
                } else if ((r==1)&&(c==0)) {            //sum of diagnal 3
                    while (startR<5&&startC<4) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC++;
                    }
                }
                if (r==0&&c==0) {                   //store the sum of diagnal 1
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal1value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal1value = holdneg;
                        }
                    }
                } else if (r==0&&c==1) {            //store sum of diagnal 2
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal2value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal2value = holdneg;
                        }
                    }
                } else if (r==1&&c==0) {            //store of sum of diagnal 3
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal3value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal3value = holdneg;
                        }
                    }
                }
            }
        }
    }

    for (int r=0; r<=1;r++) {                  //start of calculating the other side sum of diagnal
        //start diagnal on the other side of the board
        for (int c=4; c>=3;c--) {
            countsumdiagnal = 0;
            if (r==1 && c==3) {
                break;
            } else {
                int startR = r, startC =c;
                if ((r==0)&&(c==4)) {           //sum of diagnal 4
                    while (startR<5&&startC>=0) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC--;
                    }
                } else if ((r==0)&&(c==3)) {        //sum of diagnal 5
                    while (startR<4&&startC>=0) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC--;
                    }
                } else if ((r==1)&&(c==4)) {        //sum of diagnal 6
                    while (startR<5&&startC>0) {
                        countsumdiagnal+=(board->_grid[startR][startC]);
                        startR++;
                        startC--;
                    }
                }
                if (r==0&&c==4) {               //store of sum of diagnal 4
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal4value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal4value = holdneg;
                        }
                    }
                } else if (r==0&&c==3) {            //store of sum of diagnal 5
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal5value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal5value = holdneg;
                        }
                    }
                } else if (r==1&&c==4) {            //store of sum of diagnal 6
                    if(countsumdiagnal > holdpos) {
                        holdpos =  countsumdiagnal;
                        if(holdpos >= abs(holdneg)) {
                            bestdiagnal6value = holdpos;
                        }
                    } else if (countsumdiagnal < holdneg) {
                        holdneg = countsumdiagnal;
                        if (abs(holdneg)>holdpos) {
                            bestdiagnal6value = holdneg;
                        }
                    }
                }
            }
        }
    }

    //test if which diagnal has the greatest value and store the starting cell of that coordinate

    if((abs(bestdiagnal1value)>=abs(bestdiagnal2value))&&(abs(bestdiagnal1value)>=abs(bestdiagnal3value))&&(abs(bestdiagnal1value)>=abs(bestdiagnal4value))&&(abs(bestdiagnal1value)>=abs(bestdiagnal5value))&&(abs(bestdiagnal1value)>=abs(bestdiagnal6value))) {
        bestdiagoverall=bestdiagnal1value;
        diagnacoor = board->coordinateToIndex(0,0);
    } else if((abs(bestdiagnal2value)>abs(bestdiagnal1value))&&(abs(bestdiagnal2value)>=abs(bestdiagnal3value))&&(abs(bestdiagnal2value)>=abs(bestdiagnal4value))&&(abs(bestdiagnal2value)>=abs(bestdiagnal5value))&&(abs(bestdiagnal2value)>=abs(bestdiagnal6value))) {
        bestdiagoverall = bestdiagnal2value;
        diagnacoor = board->coordinateToIndex(0,1);
    } else if((abs(bestdiagnal3value)>abs(bestdiagnal1value))&&(abs(bestdiagnal3value)>abs(bestdiagnal2value))&&(abs(bestdiagnal3value)>=abs(bestdiagnal4value))&&(abs(bestdiagnal3value)>=abs(bestdiagnal5value))&&(abs(bestdiagnal3value)>=abs(bestdiagnal6value))) {
        bestdiagoverall = bestdiagnal3value;
        diagnacoor = board->coordinateToIndex(1,0);
    } else if((abs(bestdiagnal4value)>abs(bestdiagnal1value))&&(abs(bestdiagnal4value)>abs(bestdiagnal2value))&&(abs(bestdiagnal4value)>abs(bestdiagnal3value))&&(abs(bestdiagnal4value)>=abs(bestdiagnal5value))&&(abs(bestdiagnal4value)>=abs(bestdiagnal6value))) {
        bestdiagoverall = bestdiagnal4value;
        diagnacoor = board->coordinateToIndex(0,4);
    } else if((abs(bestdiagnal5value)>abs(bestdiagnal1value))&&(abs(bestdiagnal5value)>abs(bestdiagnal2value))&&(abs(bestdiagnal5value)>abs(bestdiagnal3value))&&(abs(bestdiagnal5value)>abs(bestdiagnal4value))&&(abs(bestdiagnal5value)>=abs(bestdiagnal6value))) {
        bestdiagoverall = bestdiagnal5value;
        diagnacoor = board->coordinateToIndex(0,3);
    } else if((abs(bestdiagnal6value)>abs(bestdiagnal1value))&&(abs(bestdiagnal6value)>abs(bestdiagnal2value))&&(abs(bestdiagnal6value)>abs(bestdiagnal3value))&&(abs(bestdiagnal6value)>abs(bestdiagnal4value))&&(abs(bestdiagnal6value)>abs(bestdiagnal5value))) {
        bestdiagoverall = bestdiagnal6value;
        diagnacoor = board->coordinateToIndex(1,4);
    }
    for (int row = 0; row <= gridlength; row++) {           //start of row and column calculation
        //counting row for best row value
        if ((abs(countsumrow)) >= (abs(countsumcolumn))) {  //store row value
            if(countsumrow > holdpos) {
                holdpos = countsumrow;
                if(holdpos > abs(holdneg)) {
                    bestrow = (row-1);
                    bestrowvalue = holdpos;
                }
            } else if (countsumrow < holdneg) {
                holdneg = countsumrow;
                if (abs (holdneg)>=holdpos) {
                    bestrow=(row-1);
                    bestrowvalue = holdneg;
                }
            }
        } else {
            if(countsumcolumn > holdpos) {              //store column value
                holdpos = countsumcolumn;
                if(holdpos > abs(holdneg)) {
                    bestcolumn = (row-1);
                    // find way to count column
                    bestcolumnvalue = holdpos;
                }
            } else if (countsumcolumn < holdneg) {
                holdneg = countsumcolumn;
                if (abs (holdneg)>=holdpos) {
                    bestcolumn=(row-1);
                    bestcolumnvalue = holdneg;
                }
            }
        }
        countsumrow = 0;
        countsumcolumn = 0;
        if (row < gridlength) {
            for (int column = 0;column <gridlength;column++) {
                countsumrow=countsumrow+(board->_grid[row][column]);
                countsumcolumn += (board->_grid[column][row]);
            }
        }
    }
    if (board->getMoveCount() <=1) {                        //start of game put x/0 at these coordinate
        if((board->_grid[2][2])==1 || (board->_grid[2][2])==-1) {
            temp = board->coordinateToIndex(3,3);
        } else {
            temp = board->coordinateToIndex(2,2);
        }
    }

    if(board->getMoveCount()>1) {                           //after first move, enter the algorithm and calculate where to put base on the score plus array weight above
        if((abs(bestrowvalue)>=abs(bestcolumnvalue))&&(abs(bestrowvalue)>=abs(bestdiagoverall))) {
            int index=0;
            for (int i=0;i<gridlength;i++) {
                if ((board->_grid[bestrow][i])==0) {
                    //this is scanning row
                    if((array[bestrow][i])>=(array[bestrow][index])) {
                        temp = board->coordinateToIndex(bestrow,i);
                        index =i;
                    }
                }
            }
        } else if((abs(bestcolumnvalue)>abs(bestrowvalue))&&(abs(bestcolumnvalue)>=abs(bestdiagoverall))) {
            int index =0;
            for (int i=0; i<gridlength; i++) {
                if ((board->_grid[i][bestcolumn])==0) {
                    //this is scanning column
                    if((array[i][bestcolumn])>=(array[index][bestcolumn])) {
                        temp = board->coordinateToIndex(i,bestcolumn);
                        index =i;
                    }
                }
            }
        } else if((abs(bestdiagoverall)>abs(bestcolumnvalue))&&(abs(bestdiagoverall)>abs(bestrowvalue))) {
            int Row=0;
            int Column=0;
            Row = board->indexToRow(diagnacoor);
            Column = board->indexToColumn(diagnacoor);
            int index = 0;
            int index1=0;
            if ((Row == 0)&&(Column==0)) {
                int c=Row;
                int d=Column;
                index = Row;
                index1 = Column;
                while(c<5&&d<5) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d++;
                }
            } else if ((Row == 0)&&(Column==1)) {
                int c=Row;
                int d=Column;
                index=Row;
                index1=Column;
                while(c<4&&d<5) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d++;
                }
            } else if ((Row == 1)&&(Column==0)) {
                int c=Row;
                int d=Column;
                index = c;
                index1 = d;
                while(c<5&&d<4) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d++;
                }
            } else if ((Row == 0)&&(Column==4)) {
                int c=Row;
                int d=Column;
                index =c;
                index1 = d;
                while(c<5&&d>=0) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d--;
                }
            } else if ((Row == 0)&&(Column==3)) {
                int c=Row;
                int d=Column;
                index=c;
                index1 =d;
                while(c<4&&d>=0) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d--;
                }
            } else if ((Row == 1)&&(Column==4)) {
                int c=Row;
                int d=Column;
                index =c;
                index=d;
                while(c<5&&d>0) {
                    if((board->_grid[c][d])==0) {
                        if((array[c][d])>=(array[index][index1])) {
                            temp = board->coordinateToIndex(c,d);
                            index = c;
                            index1=d;

                        }
                    }
                    c++;
                    d--;
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
    qDebug() << "Difficulty setting:" << _difficulty;
}
