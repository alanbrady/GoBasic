#include "gamelogic.h"
#include <QDebug>
#include "abstractplayer.h"

GameLogic::GameLogic(BoardMatrix *board, AbstractPlayer *p1, AbstractPlayer *p2) :
    m_board(board),
    m_p1(p1),
    m_p2(p2)
{
    //  TODO: Add a check to make sure p1 and p2 have different colors

    if (p1->color() == AbstractPlayer::WHITE)
        m_activePlayer = p1;
    else
        m_activePlayer = p2;

    emit playerChanged(m_activePlayer);
}

bool GameLogic::checkCaptures(const BoardMatrix::StateFlag& flag)
// Checks if a flag (White or Black) has any captures
// Flag necessary for context
// Remove captured pieces
{
    PieceTable checked;
    bool piecesCapped = false;
    QSize bsize = m_board->getSize();
    for (int j = 0; j < bsize.width(); j++) {
        for (int k = 0; k < bsize.height(); k++) {
            if (checked.contains(qMakePair(j, k))) {
                continue;
            }
            if (m_board->value(j, k) == flag) {
                PieceTable linked;
                getLinked(j,k, &linked);
                if (linked.size() > 0) {
//                    qDebug() << "Linked pieces (" << j << "," << k << "): " << linked;
                    if (!piecesHaveLiberties(linked)) {
                        removePieces(linked);
                        piecesCapped = true;
                    }
                }
                checked.append(linked);
            }
        }
    }
    qDebug() << "Capped:" << piecesCapped;
    return piecesCapped;
}

bool GameLogic::playerMove(int x, int y)
// Check if a given move is legal, if so switch the active player
{
    qDebug() << "Player move: " << m_activePlayer->color();
    if (isLegalMove(x, y)) {
        if (m_activePlayer == m_p1)
            m_activePlayer = m_p2;
        else
            m_activePlayer = m_p1;

        emit playerChanged(m_activePlayer);
        return true;
    }
    return false;
}

void GameLogic::getLinked(const int x, const int y, PieceTable* linked)
// Recursively checks the board at the given x,y for pieces touching
{
    linked->append(qMakePair(x, y));
    BoardMatrix::StateFlag flag = m_board->value(x,y);
    if (!linked->contains(qMakePair(x-1, y)) && m_board->value(x-1, y) == flag) {
        getLinked(x-1, y, linked);
    }
    if (!linked->contains(qMakePair(x, y-1)) && m_board->value(x, y-1) == flag) {
        getLinked(x, y-1, linked);
    }
    if (!linked->contains(qMakePair(x+1, y)) && m_board->value(x+1, y) == flag) {
        getLinked(x+1, y, linked);
    }
    if (!linked->contains(qMakePair(x, y+1)) && m_board->value(x, y+1) == flag) {
        getLinked(x, y+1, linked);
    }
}

bool GameLogic::piecesHaveLiberties(GameLogic::PieceTable pieces)
// Checks if a list of linked pieces have any liberties
{
    for (int i = 0; i < pieces.size(); i++) {
        int px = pieces.value(i).first;
        int py = pieces.value(i).second;
        if (m_board->value(px-1, py) == BoardMatrix::Empty)
            return true;
        else if (m_board->value(px, py-1) == BoardMatrix::Empty)
            return true;
        else if (m_board->value(px+1, py) == BoardMatrix::Empty)
            return true;
        else if (m_board->value(px, py+1) == BoardMatrix::Empty)
            return true;
    }
    return false;
}

void GameLogic::removePieces(GameLogic::PieceTable pieces)
// Remove a list of pieces
{
    for (int i = 0; i < pieces.size(); i++) {
        int px = pieces.at(i).first;
        int py = pieces.at(i).second;
        m_board->setValue(px, py, BoardMatrix::Empty);
    }
}

bool GameLogic::isLegalMove(const int x, const int y)
// Checks if a given move is legal
//  a. Would a piece have any liberties at x,y?
//  b. If no liberties, would move x,y result in a capture (resulting in a liberty)?
//  c. If it is a legal move, perform move, if not restore board
{
    if (m_board->value(x, y) == BoardMatrix::Empty) {
        BoardMatrix::StateFlag pcol;
        BoardMatrix::StateFlag ocol;
        if (m_activePlayer->color() == AbstractPlayer::BLACK) {
            pcol = BoardMatrix::BlackPiece;
            ocol = BoardMatrix::WhitePiece;
        } else {
            pcol = BoardMatrix::WhitePiece;
            ocol = BoardMatrix::BlackPiece;
        }

        PieceTable linked;
        m_board->setValue(x,y, pcol);
        getLinked(x,y,&linked);
        if (piecesHaveLiberties(linked)) {
            qDebug() << "Linked: " << linked;
            checkCaptures(ocol);
            return true;
        } else if (checkCaptures(ocol)) {
            return true;
        }
//        } else if (pcol == AbstractPlayer::WHITE){
//            m_board->setValue(x,y, BoardMatrix::WhitePiece);
//            getLinked(x,y,&linked);
//            if (piecesHaveLiberties(linked)) {
//                qDebug() << "Linked: " << linked;
//                checkCaptures(BoardMatrix::BlackPiece);
//                return true;
//            } else if (checkCaptures(BoardMatrix::BlackPiece)) {
//                return true;
//            }
//        }
        qDebug() << "No liberties or captures";
        //(*m_board) = oldBoard;
        m_board->setValue(x,y, BoardMatrix::Empty);
        return false;
    } else return false;
}

bool GameLogic::start()
// Start and initialize a game.
{
    m_status = RUNNING;
    return true;
}
