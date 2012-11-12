#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QWidget>
#include <QSize>
#include <QPair>
#include <QList>
#include "boardmatrix.h"
#include "abstractplayer.h"

//class AbstractPlayer;

class GameLogic : public QWidget
{
    Q_OBJECT

public:
    GameLogic(BoardMatrix* board, AbstractPlayer* p1, AbstractPlayer* p2);

    enum Status {
        RUNNING,
        STOPPED,
        GAMEOVER
    };

    typedef QList<QPair<int, int> > PieceTable;

    Status status() const { return m_status; }
    bool start();
    bool stop() { m_status = STOPPED; return true; }
    bool checkCaptures(const BoardMatrix::StateFlag &flag);
    bool playerMove(int x, int y);
    const AbstractPlayer* getActivePlayer() { return m_activePlayer; }

signals:
    void playerChanged(AbstractPlayer*);

private:
    Status m_status;
    BoardMatrix* m_board;
    AbstractPlayer* m_p1;
    AbstractPlayer* m_p2;
    AbstractPlayer* m_activePlayer;

    void getLinked(const int x, const int y, PieceTable *linked);
    bool piecesHaveLiberties(PieceTable pieces);
    void removePieces(PieceTable pieces);
    bool isLegalMove(const int x, const int y);
};

#endif // GAMELOGIC_H
