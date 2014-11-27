#include "parsehelper.h"
#include <QDebug>
#include <QUrlQuery>

void ParseHelper::setContentLength(int size){
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", QByteArray(QString::number(size).toUtf8()));
}

ParseHelper::ParseHelper(QObject *parent) : QObject(parent)
{
    request.setRawHeader("User-Agent", "4Stones");
    request.setRawHeader("X-Custom-User-Agent", "4Stones");
    request.setRawHeader("X-Parse-Application-Id", "BCb5kAR9qnajuBhXpzoA8e8dOdzOdMds04sEUJJd");
    request.setRawHeader("X-Parse-REST-API-Key","Orlu3hoJgkINylZBUoiDaQRjQmpC31a1D4qoZa2D");
}

void ParseHelper::login(QString username){
    connect(netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleLogin(QNetworkReply*)));
    QUrlQuery qq;
    qq.addQueryItem("username", username);
    qq.addQueryItem("password", username);
    QUrl q = QUrl("https://api.parse.com/1/login");
    q.setQuery(qq);
    request.setUrl(q);
    netManager->get(request);
}

void ParseHelper::registerPlayer(QString username){
    connect(netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleRegister(QNetworkReply*)));
    request.setUrl(QUrl("https://api.parse.com/1/users"));
    QJsonObject json;
    json.insert("username", username);
    json.insert("password", username);
    json.insert("win", 0);
    json.insert("loss", 0);
    json.insert("draw", 0);
    QByteArray jsonString = QJsonDocument(json).toJson();
    setContentLength(jsonString.size());
    netManager->post(request, jsonString);
}

void ParseHelper::handleLogin(QNetworkReply* reply){
    emit loginFinished((reply->errorString() == "Unknown error"), reply);
}

void ParseHelper::handleRegister(QNetworkReply* reply){
    emit registerFinished((reply->errorString() == "Unknown error"), reply);
}
