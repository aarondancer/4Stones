#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "parsehelper.h"
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

class Player : public QObject{
    Q_OBJECT

    Q_PROPERTY(int wins READ getWins WRITE setWins NOTIFY winsChanged)
    Q_PROPERTY(int losses READ getLosses WRITE setLosses NOTIFY lossesChanged)
    Q_PROPERTY(int draws READ getDraws WRITE setDraws NOTIFY drawsChanged)
    Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)

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

    Q_INVOKABLE void loginPlayer(QString username);
    Q_INVOKABLE void registerPlayer(QString username);
    Q_INVOKABLE void updatePlayer(int wins, int losses, int draws);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void deletePlayer();

signals:
    void usernameChanged();
    void drawsChanged();
    void lossesChanged();
    void winsChanged();
    void numberChanged();
    void loginFinished();
    void loginFailed();
    void registerFinished();
    void registerFailed();

public slots:
    void handleLogin(bool exists, QNetworkReply *reply);
    void handleRegister(bool exists, QNetworkReply *reply);

private:
    int _wins;
    int _losses;
    int _draws;
    int _number;
    QString _username;
    QString objectID;
    QString session;
};

#endif // PLAYER_H
