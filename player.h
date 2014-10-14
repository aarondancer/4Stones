#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int wins READ getWins WRITE setWins NOTIFY winsChanged)

public:
    explicit Player(QObject *parent = 0);
    void makeMove(int index);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getDraws() const;
    void setDraws(int value);

signals:
    void winsChanged();

public slots:

private:
    int _wins;
    int _losses;
    int _draws;
};

#endif // PLAYER_H
