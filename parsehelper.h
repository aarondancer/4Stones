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

    void login(QString username);
    void registerPlayer(QString username);
    void updatePlayer(QString id, QString session, int wins, int losses, int draws);
    void deletePlayer(QString id, QString session);

private:
    QNetworkAccessManager* netManager;
    QNetworkRequest request;
    void setContentLength(int size);
    void setSession(QString session);

signals:
    void loginFinished(bool exists, QNetworkReply* reply);
    void registerFinished(bool exists, QNetworkReply* reply);

public slots:
    void handleLogin(QNetworkReply* reply);
    void handleRegister(QNetworkReply* reply);
    void handleUpdate(QNetworkReply* reply);
};

#endif // PARSEHELPER_H
