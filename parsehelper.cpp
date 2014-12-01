#include "parsehelper.h"
#include <QDebug>
#include <QUrlQuery>


ParseHelper::ParseHelper(QObject *parent) : QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    request.setRawHeader("User-Agent", "4Stones");
    request.setRawHeader("X-Custom-User-Agent", "4Stones");
    request.setRawHeader("X-Parse-Application-Id", "BCb5kAR9qnajuBhXpzoA8e8dOdzOdMds04sEUJJd");
    request.setRawHeader("X-Parse-REST-API-Key","Orlu3hoJgkINylZBUoiDaQRjQmpC31a1D4qoZa2D");
}

ParseHelper::~ParseHelper() {
    delete netManager;
}

void ParseHelper::setContentLength(int size){
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", QByteArray(QString::number(size).toUtf8()));
}

void ParseHelper::setSession(QString session){
    request.setRawHeader("X-Parse-Session-Token", QByteArray(session.toUtf8()));
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

void ParseHelper::updatePlayer(QString id, QString session, int wins, int losses, int draws){
    setSession(session);
//    connect(netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleUpdate(QNetworkReply*)));
    request.setUrl(QUrl("https://api.parse.com/1/users/" + id));
    QJsonObject json;
    json.insert("win", wins);
    json.insert("loss", losses);
    json.insert("draw", draws);
    QByteArray jsonString = QJsonDocument(json).toJson();
    setContentLength(jsonString.size());
    netManager->put(request, jsonString);
}

void ParseHelper::handleUpdate(QNetworkReply *reply){
    qDebug() << reply->readAll();
    qDebug() << reply->errorString();
}

void ParseHelper::deletePlayer(QString id, QString session){
    setSession(session);
    request.setUrl(QUrl("https://api.parse.com/1/users/" + id));
    netManager->deleteResource(request);
}

