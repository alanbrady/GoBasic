#include "abstractplayer.h"
#include "gamelogic.h"


AbstractPlayer::AbstractPlayer(GameLogic *logic, Color color, QObject *parent) :
    QObject(parent),
    m_logic(logic),
    m_color(color),
    m_isActive(false),
    m_points(0),
    m_name("SomeName")
{}

void AbstractPlayer::startTurn() {
    m_isActive = true;
    this->doTurn();
}

bool AbstractPlayer::doMove(int x, int y)
{
    if (m_isActive) {
        bool success = m_logic->playerMove(x, y);
        if (success) { m_isActive = false; }
        return success;
    }
    return false;
}
