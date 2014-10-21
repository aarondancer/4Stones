#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int wins READ getWins WRITE setWins NOTIFY winsChanged)
    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)

public:
    explicit Player(QObject *parent = 0);

    int getWins() const;
    void setWins(int value);

    int getLosses() const;
    void setLosses(int value);

    int getDraws() const;
    void setDraws(int value);

    int getNumber() const;
    void setNumber(int number);

signals:
    void winsChanged();
    void numberChanged();

public slots:

private:
    int _wins;
    int _losses;
    int _draws;
    int _number;
};

#endif // PLAYER_H
