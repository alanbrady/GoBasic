#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "abstractplayer.h"

class HumanPlayer : public AbstractPlayer
{
public:
    HumanPlayer(QString name, GameLogic* logic, Color color, QObject* parent = 0);

    const bool isHuman() const { return true; }
    void doTurn() {}

};

#endif // HUMANPLAYER_H
