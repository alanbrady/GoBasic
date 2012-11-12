#include "gameboardwidget.h"
#include "ui_gameboardwidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QSize>
#include <math.h>

#include <QDebug>

const char* GameBoardWidget::BoardImagePath = "./wood.jpg";
const char* GameBoardWidget::WhitePieceImagePath = "./white.png";
const char* GameBoardWidget::BlackPieceImagePath = "./black.png";

GameBoardWidget::GameBoardWidget(QWidget *parent, BoardMatrix *board, QSize size, quint8 gridSize) :
    QWidget(parent),
    ui(new Ui::GameBoardWidget),
    m_size(size),
    m_bx(-1),
    m_by(-1),
    m_gridSize(gridSize),
    m_board(board),
    m_boardBorder(8),
    m_gridBorder(30),
    m_highlightWidth(6)
{

    ui->setupUi(this);
    if (!m_woodImg.load(BoardImagePath))
        QMessageBox::warning(this, "Unable to load!", "Unable to load board!", QMessageBox::Ok);

    if (!m_blackImg.load(BlackPieceImagePath))
        QMessageBox::warning(this, "Unable to load!", "Unable to load black piece image!", QMessageBox::Ok);

    if (!m_whiteImg.load(WhitePieceImagePath))
        QMessageBox::warning(this, "Unable to load!", "Unable to load white piece image!", QMessageBox::Ok);

    this->setMouseTracking(true);
    makeGridRect();
}

GameBoardWidget::~GameBoardWidget()
{
    delete ui;
}

void GameBoardWidget::paintEvent(QPaintEvent * event) {
    QPainter painter(this);

    drawBoard(&painter);
    drawGrid(&painter);
    drawPieces(&painter);
    drawHighlight(&painter);
}

void GameBoardWidget::mouseMoveEvent(QMouseEvent *e) {
    float mx = e->x()-m_gridRect.x();
    float my = e->y()-m_gridRect.y();
    float gridSpace = getGridSpace();
    int bx = floor((mx / gridSpace)+0.5);
    int by = floor((my / gridSpace)+0.5);
    if (bx != m_bx || by != m_by) {
        m_bx = bx;
        m_by = by;
        repaint();
    }
}

void GameBoardWidget::mousePressEvent(QMouseEvent *e)
{
    emit clicked();
}

void GameBoardWidget::sizeChanged(QSize size) {
    m_size = size - QSize(m_boardBorder*2,m_boardBorder*2);
    this->resize(size - QSize(0, 0));
    makeGridRect();
}

void GameBoardWidget::drawBoard(QPainter *painter) {
    quint32 k = m_size.height() > m_size.width() ? m_size.height() : m_size.width();
    QImage scaledboard = m_woodImg.scaledToHeight(k);
    painter->drawImage(m_boardBorder, m_boardBorder , scaledboard, 0, 0, m_size.width(), m_size.height());
    painter->setPen(QPen(QColor(0,0,0,200), 2));
    painter->drawRect(m_boardBorder, m_boardBorder, m_size.width(), m_size.height());

}

void GameBoardWidget::drawGrid(QPainter *painter) {
    QRect tempRect = m_gridRect;
    tempRect.adjust(-1, -1, -1, -1);
    QPen pen(QColor(155,155,155,150), 1.5);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(tempRect);
    pen.setColor(QColor(0,0,0,200));
    painter->setPen(pen);
    painter->drawRect(m_gridRect);

    quint32 gridSpace = getGridSpace();
    for (int i = 1; i < m_gridSize-1; i++) {
        if (i != m_bx)
        painter->drawLine(m_gridRect.x()+(gridSpace*i), m_gridRect.y(),
                          m_gridRect.x()+(gridSpace*i), m_gridRect.height()+m_gridRect.y());
        if (i != m_by)
        painter->drawLine(m_gridRect.x(), (gridSpace*i)+m_gridRect.y(),
                          m_gridRect.width()+m_gridRect.x(), (gridSpace*i)+m_gridRect.y());

    }
}

void GameBoardWidget::drawPieces(QPainter *painter) {
    const quint32 gridSpace = getGridSpace();
    const quint32 imgWidth = m_blackImg.size().width();
    const quint32 imgHeight = m_blackImg.size().height();
    for (int j = 0; j < m_board->getSize().height(); j++) {
        for (int k = 0; k < m_board->getSize().width(); k++) {
            const BoardMatrix::StateFlag flag = m_board->value(j, k);
            int x = ((gridSpace*j)-(imgWidth/2))+m_gridRect.x();
            int y = ((gridSpace*k)-(imgHeight/2))+m_gridRect.y();
            switch(flag) {
                case BoardMatrix::BlackPiece:
                    painter->drawImage(x, y, m_blackImg);
                    break;
                case BoardMatrix::WhitePiece:
                    painter->drawImage(x, y, m_whiteImg);
                    break;
                default:
                    break;
            }
        }
    }
}

void GameBoardWidget::drawHighlight(QPainter *painter) {
    const quint32 gridSpace = getGridSpace();
    painter->setBrush(QColor(200,0,0,100));
    painter->setPen(QColor(200,0,0,100));

    QRect rect1(m_gridRect.x()+(gridSpace*m_bx)-(m_highlightWidth/2),
                m_gridRect.y(), m_highlightWidth, m_gridRect.height());
    if (rect1.x() < m_gridRect.x()) {
        rect1.setX(m_gridRect.x()+1);
        rect1.setWidth(m_highlightWidth);
    }
    painter->drawRect(rect1);

    QRect rect2(m_gridRect.x(), m_gridRect.y()+(gridSpace*m_by)-(m_highlightWidth/2),
                m_gridRect.width(), m_highlightWidth);
    if (rect2.y() < m_gridRect.y()) {
        rect2.setY(m_gridRect.y()+1);
        rect2.setHeight(m_highlightWidth);
    }
    painter->drawRect(rect2);

}

const quint32 GameBoardWidget::getGridSpace() const {
    quint32 s = m_gridRect.width() / (m_gridSize-1);
    return s;
}

void GameBoardWidget::makeGridRect() {
    int dim = (m_size.width() - (m_boardBorder*2));
    int difMod = dim % (m_gridSize-1);
    dim = dim - difMod - m_boardBorder - m_gridBorder;
    m_gridRect = QRect(m_boardBorder+m_gridBorder+(difMod/2),m_boardBorder+m_gridBorder+(difMod/2), dim, dim);
}
