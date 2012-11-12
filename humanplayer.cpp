#include "humanplayer.h"

HumanPlayer::HumanPlayer(GameLogic *logic, AbstractPlayer::Color color, QObject *parent)
    : AbstractPlayer(logic, color, parent)
{
}
