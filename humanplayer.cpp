#include "humanplayer.h"

HumanPlayer::HumanPlayer(QString name, GameLogic *logic, AbstractPlayer::Color color, QObject *parent)
    : AbstractPlayer(name, logic, color, parent)
{
}
