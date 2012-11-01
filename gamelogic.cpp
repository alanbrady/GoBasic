#include "gamelogic.h"

#include <QDebug>

GameLogic::GameLogic(BoardMatrix *board) :
    m_board(board)
{

}

bool GameLogic::checkCaptures(const BoardMatrix::StateFlag& flag)
{
    PieceTable checked;
    bool piecesCapped = false;
    QSize bsize = m_board->getSize();
    for (int j = 0; j < bsize.width(); j++) {
        for (int k = 0; k < bsize.height(); k++) {
            if (checked.contains(qMakePair(j, k))) {
                continue;
            }
            if (m_board->value(j, k) == flag/*BoardMatrix::BlackPiece || m_board->value(j, k) == BoardMatrix::WhitePiece*/) {
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
    return piecesCapped;
}

bool GameLogic::playerMove(int x, int y)
{
    return true;
}

AbstractPlayer *GameLogic::activePlayer()
{
    return 0;
}

void GameLogic::getLinked(const int x, const int y, PieceTable* linked)
{
    // Recursively checks the board at the given x,y for pieces touching
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
{
    for (int i = 0; i < pieces.size(); i++) {
        int px = pieces.at(i).first;
        int py = pieces.at(i).second;
        m_board->setValue(px, py, BoardMatrix::Empty);
    }
}

bool GameLogic::isLegalMove(const int x, const int y)
{
    if (m_board->value(x, y) == BoardMatrix::Empty) {
        BoardMatrix oldBoard = *m_board;
        AbstractPlayer::Color pcol = activePlayer()->color();
        if (pcol == AbstractPlayer::BLACK) {
            m_board->setValue(x,y, BoardMatrix::BlackPiece);
            if (checkCaptures(BoardMatrix::WhitePiece)) {
                checkCaptures(BoardMatrix::BlackPiece);
                return true;
//                PieceTable linked;
//                getLinked(x, y, &linked);
//                if (piecesHaveLiberties(linked)) {
//                    return true;
//                } else {
//                    (*m_board) = oldBoard;
//                    return false;
//                }
            } else {
                if (checkCaptures(BoardMatrix::BlackPiece)) {
                    (*m_board) = oldBoard;
                    return false;
                } else
                    return true;
            }
        } else if (pcol == AbstractPlayer::WHITE){
            m_board->setValue(x,y, BoardMatrix::WhitePiece);
            if (checkCaptures(BoardMatrix::BlackPiece)) {
                checkCaptures(BoardMatrix::WhitePiece);
                return true;
//                PieceTable linked;
//                getLinked(x, y, &linked);
//                if (piecesHaveLiberties(linked)) {
//                    return true;
//                } else {
//                    (*m_board) = oldBoard;
//                    return false;
//                }
            } else {
                if (checkCaptures(BoardMatrix::WhitePiece)) {
                    (*m_board) = oldBoard;
                    return false;
                } else
                    return true;
            }

        }
        (*m_board) = oldBoard;
        return false;
        PieceTable linked;
        getLinked(x, y, &linked);
        if (piecesHaveLiberties(linked)) {
            return true;
        }
    } else return false;
}
