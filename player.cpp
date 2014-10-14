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

void Player::makeMove(int index){

}

