#ifndef GAMEBOARDFORM_H
#define GAMEBOARDFORM_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QSize>
#include <Q_UINT8>
#include <Q_INT32>
#include <QRect>

#include "boardmatrix.h"

namespace Ui {
    class GameBoardWidget;
}

class GameBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoardWidget(QWidget *parent, BoardMatrix* board, QSize size, quint8 gridSize = 9);
    ~GameBoardWidget();

    const static char* BoardImagePath;
    const static char* BlackPieceImagePath;
    const static char* WhitePieceImagePath;

    const int getBoardX() { return m_bx; }
    const int getBoardY() { return m_by; }

public slots:
    void sizeChanged(QSize size);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::GameBoardWidget *ui;
    QImage m_woodImg;
    QImage m_blackImg;
    QImage m_whiteImg;
    QSize m_size;
    QRect m_gridRect;
    char m_bx;
    char m_by;
    quint8 m_gridSize;
    BoardMatrix *m_board;
    const quint8 m_boardBorder;
    const quint8 m_gridBorder;
    const quint8 m_highlightWidth;

    void drawBoard(QPainter* painter);
    void drawGrid(QPainter* painter);
    void drawPieces(QPainter* painter);
    void drawHighlight(QPainter* painter);
    const quint32 getGridSpace() const;
    void makeGridRect();
};

#endif // GAMEBOARDFORM_H
