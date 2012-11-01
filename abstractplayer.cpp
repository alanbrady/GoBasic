#include "abstractplayer.h"
#include "gamelogic.h"


AbstractPlayer::AbstractPlayer(GameLogic *log, Color color, QObject *parent) :
       QObject(parent),
       m_logic(log),
       m_color(color)
{

}


bool AbstractPlayer::doMove(int x, int y)
{
    return m_logic->playerMove(x, y);
}
