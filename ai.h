#ifndef AI_H
#define AI_H

#import "player.h"

class AI : public Player
{

public:
    AI();
    Q_INVOKABLE void makeMove(int index);
};

#endif // AI_H
