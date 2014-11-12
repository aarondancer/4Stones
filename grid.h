//Acts as a grid and provides the functions relating to modifying the grid
//DOES NOT provide a GUI

#ifndef GRID_H
#define GRID_H

#include <QObject>

class Grid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList< QList<int> > grid READ getGrid NOTIFY idkwhattodowithnotify) //2D Array representing the grid
    Q_PROPERTY(int gridLength READ getGridLength WRITE setGridLength NOTIFY idkwhattodowithnotify) //Vertical length of the grid
    Q_PROPERTY(int lastMove READ getLastMove WRITE setLastMove NOTIFY idkwhattodowithnotify) //Location of the last stone placed. Used for win-checking optimization
    Q_PROPERTY(int countToWin READ getCountToWin WRITE setCountToWin NOTIFY idkwhattodowithnotify) //Number of stones needed in a row to win
    Q_PROPERTY(int lastMoveX READ lastMoveX WRITE setLastMoveX NOTIFY idkwhattodowithnotify)
    Q_PROPERTY(int lastMoveO READ lastMoveO WRITE setlastMoveO NOTIFY idkwhattodowithnotify)

public:
    explicit Grid(QObject *parent = 0);

    //Getters and Setters

    QList< QList<int> > getGrid(){ return _grid; }

    int getGridLength(){ return _gridLength; }

    void setGridLength(const int length){ _gridLength = length; }

    int getLastMove(){ return _lastMove; }

    void setLastMove(const int player){ _lastMove = player; }

    int getCountToWin(){ return _countToWin; }

    void setCountToWin(const int count){ _countToWin = count; }

    //Player Related

    Q_INVOKABLE void placePiece(const int index, const int player);

    //Win Checking

    Q_INVOKABLE bool checkWin(int player); //Win-checking algorithm. Only checks areas within range given by countToWin of the lastMove

    //1D-2D bridge

    Q_INVOKABLE int indexToRow(int index); //Returns the respective row of 2D array given index of 1D array

    Q_INVOKABLE int indexToColumn(int index); //Returns the respective column of 2D array given index of 1D array

    Q_INVOKABLE int coordinateToIndex(int row, int column); //Returns the respective index of 1D array given coordinate of 2D array

    Q_INVOKABLE int valueFromIndex(int index); //get the value from the 2D array given the index of the 1D array

    Q_INVOKABLE bool isFilled();

    QList< QList<int> > _grid;

    Q_INVOKABLE void boardReset();

    int lastMoveX() const;
    void setLastMoveX(int lastMoveX);

    int lastMoveO() const;
    void setlastMoveO(int lastMoveO);

signals:
    void idkwhattodowithnotify();

public slots:

private:
    int _lastMove;
    int _gridLength;
    int _countToWin;
    int _lastMoveX;
    int _lastMoveO;
};

#endif // GRID_H
