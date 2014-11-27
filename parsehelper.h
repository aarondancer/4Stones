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

    void login(QString username);
    void registerPlayer(QString username);

private:
    QNetworkAccessManager* netManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    void setContentLength(int size);

signals:
    void loginFinished(bool exists, QNetworkReply* reply);
    void registerFinished(bool exists, QNetworkReply* reply);

public slots:
    void handleLogin(QNetworkReply* reply);
    void handleRegister(QNetworkReply* reply);
};

#endif // PARSEHELPER_H
