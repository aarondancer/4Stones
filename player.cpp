#include "player.h"
#include <QDebug>
#include <QMessageBox>
#include <QQuickView>

Player::Player(QObject *parent) : QObject(parent)
{
    _username = "";
}

int Player::getWins() const
{
    return _wins;
}

void Player::setWins(int value)
{
    _wins = value;
}
int Player::getLosses() const
{
    return _losses;
}

void Player::setLosses(int value)
{
    _losses = value;
}

int Player::getDraws() const
{
    return _draws;
}

void Player::setDraws(int value)
{
    _draws = value;
}

int Player::getNumber() const
{
    return _number;
}

void Player::setNumber(int number)
{
    _number = number;
}

void Player::getSetPlayer(QString username)
{
    _username = username;
    QString url_str = "https://BCb5kAR9qnajuBhXpzoA8e8dOdzOdMds04sEUJJd:javascript-key=7qrW1ee95IbnO3MIA4haufNEMj2nvM1cfymEgDD3@api.parse.com/1/classes/_User";
    ParseRequestInput input(url_str, "GET");

    ParseRequestWorker *worker = new ParseRequestWorker(this);
    connect(worker, SIGNAL(on_execution_finished(ParseRequestWorker*)), this, SLOT(setPlayer(ParseRequestWorker*)));
    worker->execute(&input);
}

void Player::setPlayer(ParseRequestWorker * worker){\
    bool didSet = false;
    QJsonArray array = QJsonDocument::fromJson(worker->response).object().value("results").toArray();
    foreach(const QJsonValue &v, array){
        QJsonObject temp = v.toObject();
        if (temp.value("username").toString() == _username){
            didSet = true;
            objectID = v.toObject().value("objectID").toString();
            break;
        }
    }
    if (didSet){
        emit setPlayerFinished();
    }else{
        _username = "";
        emit setPlayerFailed();
    }
}

bool Player::registerPlayer(QString username){
    return false;
}

