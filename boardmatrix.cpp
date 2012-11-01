#include "boardmatrix.h"

BoardMatrix::BoardMatrix(int height, int width) :
    m_height(height), m_width(width), m_size(height, width)
{
    m_matrix.fill(QVector<BoardMatrix::StateFlag>().fill(BoardMatrix::Empty , m_width), m_height);

    // Delete later ****
//    m_matrix[5][5] = BoardMatrix::BlackPiece;
//    m_matrix[5][4] = BoardMatrix::BlackPiece;
//    m_matrix[5][3] = BoardMatrix::BlackPiece;

//    m_matrix[3][1] = BoardMatrix::WhitePiece;
//    m_matrix[4][1] = BoardMatrix::WhitePiece;
//    m_matrix[5][1] = BoardMatrix::WhitePiece;
    m_matrix[0][1] = BoardMatrix::WhitePiece;
    m_matrix[1][0] = BoardMatrix::WhitePiece;
    m_matrix[0][0] = BoardMatrix::BlackPiece;
}

const BoardMatrix &BoardMatrix::operator =(const BoardMatrix &other)
{
    BoardMatrix n(other.m_height, other.m_width);
    n.m_size = other.m_size;
    n.m_matrix = other.m_matrix;
    return (*this);
}

QVector<BoardMatrix::StateFlag>& BoardMatrix::operator [](const quint8 x) {
    return m_matrix[x];
}

const QVector<BoardMatrix::StateFlag>& BoardMatrix::operator [](const quint8 x) const {
    return m_matrix[x];
}

void BoardMatrix::setValue(quint8 x, quint8 y, const StateFlag f)
{
    m_matrix[x][y] = f;
}

