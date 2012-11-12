#ifndef BOARDMATRIX_H
#define BOARDMATRIX_H

#include <QVector>
#include <QSize>
#include <Q_UINT8>

class BoardMatrix
{
public:
    BoardMatrix(int height, int width);
//    const BoardMatrix& operator=(const BoardMatrix& other);

    enum StateFlag {
        Empty =             0x01,
        WhitePiece =        0x02,
        BlackPiece =        0x04,
        WhiteTerritory =    0x08,
        BlackTerritory =    0x10
    };

    QVector<StateFlag>& operator[](const quint8 x);
    const QVector<StateFlag>& operator[](const quint8 x) const;

    const QSize getSize() const { return m_size; }
    const StateFlag value(quint8 x, quint8 y) const { return m_matrix.value(x).value(y); }
    void setValue(quint8 x, quint8 y, const StateFlag f);
    void clearBoard() { m_matrix.clear(); }

private:
    const int m_height;
    const int m_width;
    QVector<QVector<StateFlag> > m_matrix;
    QSize m_size;
};

#endif // BOARDMATRIX_H
