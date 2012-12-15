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
    explicit GameBoardWidget(QWidget *parent, BoardMatrix* board, quint8 gridSize);
    ~GameBoardWidget();

    const static char* BoardImagePath;
    const static char* BlackPieceImagePath;
    const static char* WhitePieceImagePath;

    int getBoardX() const { return m_bx; }
    int getBoardY() const { return m_by; }

//public slots:
//    void sizeChanged(QSize size);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *);
    QSize sizeHint() const;
//    int heightForWidth(int w) const;

private:
    Ui::GameBoardWidget *ui;
    QImage m_woodImg;
    QImage m_blackImg;
    QImage m_whiteImg;
//    QSize m_size;
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
    quint32 getGridSpace() const;
    void makeGridRect();
};

#endif // GAMEBOARDFORM_H
