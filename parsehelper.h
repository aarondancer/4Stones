#ifndef PARSEHELPER_H
#define PARSEHELPER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

class ParseHelper : public QObject {
    Q_OBJECT
public:
    explicit ParseHelper(QObject *parent = 0);
    ~ParseHelper();

    void login(QString username); //Logs a user in given a username
    void registerPlayer(QString username); //Registers a user given a username
    void updatePlayer(QString id, QString session, int wins, int losses, int draws); //Updates a users wins, losses, and draws given the user's primary key on the database and the session token
    void deletePlayer(QString id, QString session); //Deletes a player given the user's primary key on the database and session token

private:
    QNetworkAccessManager* netManager; //Handles all http(s) requests
    QNetworkRequest request; //Content of a http(s) request
    void setContentLength(int size); //Set the length of the json content as a http request header
    void setSession(QString session); //Set the session token header of a http request given a session token

signals:
    void loginFinished(bool exists, QNetworkReply* reply); //Signals that a login has been completed
    void registerFinished(bool exists, QNetworkReply* reply); //Signals that a registration has been completed

public slots:
    void handleLogin(QNetworkReply* reply); //Handles the response from server of a login
    void handleRegister(QNetworkReply* reply); //Handles the response from server of a registration
    void handleUpdate(QNetworkReply* reply);//Hanles the response from server of updating a player
};

#endif // PARSEHELPER_H
