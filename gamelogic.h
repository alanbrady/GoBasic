#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QSize>
#include <QPair>
#include <QList>
#include "boardmatrix.h"
#include "abstractplayer.h"

class AbstractPlayer;

class GameLogic
{
public:
    GameLogic(BoardMatrix* board);

    enum Status {
        RUNNING,
        STOPPED,
        GAMEOVER
    };

    typedef QList<QPair<int, int> > PieceTable;
//    typedef QPair<int, int> Move;

    Status status() const { return m_status; }
    bool start() { m_status = RUNNING; return true; }
    bool stop() { m_status = STOPPED; return true; }
    bool checkCaptures(const BoardMatrix::StateFlag &flag);
    bool playerMove(int x, int y);
    AbstractPlayer* activePlayer();

private:
    Status m_status;
    BoardMatrix* m_board;

    void getLinked(const int x, const int y, PieceTable *linked);
    bool piecesHaveLiberties(PieceTable pieces);
    void removePieces(PieceTable pieces);
    bool isLegalMove(const int x, const int y);
};

#endif // GAMELOGIC_H
