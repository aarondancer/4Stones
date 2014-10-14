//Acts as a grid and provides the functions relating to modifying the grid
//DOES NOT provide a GUI

#ifndef GRID_H
#define GRID_H

#include "player.h"
#include <QObject>


class Grid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<int> grid READ getGrid NOTIFY idkwhattodowithnotify) //2D Array representing the grid
    Q_PROPERTY(int gridLength READ getGridLength WRITE setGridLength NOTIFY idkwhattodowithnotify) //Vertical length of the grid
    Q_PROPERTY(int lastMove READ getLastMove WRITE setLastMove NOTIFY idkwhattodowithnotify) //Location of the last stone placed. Used for win-checking optimization
    Q_PROPERTY(int countToWin READ getCountToWin WRITE setCountToWin NOTIFY idkwhattodowithnotify) //Number of stones needed in a row to win
    Q_PROPERTY(QList<Player*> players READ getPlayers NOTIFY idkwhattodowithnotify)  //2 Player Objects

public:
    explicit Grid(QObject *parent = 0);

    //Getters and Setters

    QList<int> getGrid(){ return _grid; }

    int getGridLength(){ return _gridLength; }

    void setGridLength(const int length){ _gridLength = length; }

    int getLastMove(){ return _lastMove; }

    void setLastMove(const int player){ _lastMove = player; }

    int getCountToWin(){ return _countToWin; }

    void setCountToWin(const int count){ _countToWin = count; }

    QList<Player*> getPlayers(){ return _players; }

    //Player Related

    Q_INVOKABLE void placePiece(const int index, const int player);

    //Win Checking

    Q_INVOKABLE bool checkWin(); //Win-checking algorithm. Only checks areas within range given by countToWin of the lastMove

signals:
    void idkwhattodowithnotify();

public slots:

private:
    QList<int> _grid;
    int _lastMove;
    int _gridLength;
    int _countToWin;
    QList<Player*> _players;
};

#endif // GRID_H
