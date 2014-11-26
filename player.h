#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "parserequestworker.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

using namespace std;

class Player : public QObject{
    Q_OBJECT
    Q_PROPERTY(int wins READ getWins WRITE setWins NOTIFY winsChanged)
    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername)

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

    QString getUsername() const{
        return _username;
    }

    void setUsername(QString username){
        _username = username;
    }

    Q_INVOKABLE void getSetPlayer(QString username);
    Q_INVOKABLE bool registerPlayer(QString username);

signals:
    void winsChanged();
    void numberChanged();
    void setPlayerFinished();
    void setPlayerFailed();

public slots:
    void setPlayer(ParseRequestWorker * worker);

private:
    int _wins;
    int _losses;
    int _draws;
    int _number;
    QString _username;
    QString objectID;
};

#endif // PLAYER_H
