#include "boardmatrix.h"

BoardMatrix::BoardMatrix(int height, int width) :
    m_height(height), m_width(width), m_size(height, width)
{
    m_matrix.fill(QVector<BoardMatrix::StateFlag>().fill(BoardMatrix::Empty, m_width), m_height);

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

