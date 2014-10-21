#ifndef AI_H
#define AI_H

#include <QObject>
#include "global.h"

class AI: public QObject{
    //Q_OBJECT
    Q_PROPERTY(int difficulty READ getDifficulty WRITE setDifficulty)
    public:
        explicit AI(QObject *parent = 0);
        Q_INVOKABLE void makeMove() const;
        Q_INVOKABLE int getDifficulty() const;
        Q_INVOKABLE void setDifficulty(int value);

    private:
        int _difficulty;
};

#endif // AI_H
