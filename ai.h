#ifndef AI_H
#define AI_H

<<<<<<< HEAD
#include <QObject>
#include "global.h"
=======
#include "player.h"
>>>>>>> FETCH_HEAD

class AI: public QObject{
    //Q_OBJECT
    Q_PROPERTY(short difficulty)
    public:
        explicit AI(QObject *parent = 0);
        Q_INVOKABLE void makeMove();

        short getDifficulty() const;
        void setDifficulty(short value);

    private:
        short _difficulty;
};

#endif // AI_H
