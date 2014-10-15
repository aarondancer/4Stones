#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{

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


void Player::makeMove(int index){
    board->placePiece(index, _number);
}

