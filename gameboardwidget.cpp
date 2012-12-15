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

// TODO: Completely refactor how the drawing is done for this widget, it's definitely not being done correctly

GameBoardWidget::GameBoardWidget(QWidget *parent, BoardMatrix *board, quint8 gridSize) :
    QWidget(parent),
    ui(new Ui::GameBoardWidget),
    m_bx(-1),
    m_by(-1),
    m_gridSize(gridSize),
    m_board(board),
    m_boardBorder(8),
    m_gridBorder(40),
    m_highlightWidth(6)
{

//    this->setMinimumSize(550,550);
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

void GameBoardWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    this->makeGridRect();

    drawBoard(&painter);
    drawGrid(&painter);
    drawHighlight(&painter);
    drawPieces(&painter);
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

void GameBoardWidget::mousePressEvent(QMouseEvent *) {
    emit clicked();
}

QSize GameBoardWidget::sizeHint() const {
    return QSize(550, 550);
}

//void GameBoardWidget::sizeChanged(QSize size) {
//    size = this->size();
//    qDebug() << size;

//    m_size = size - QSize(m_boardBorder*2,m_boardBorder*2);
//    m_size.setHeight(m_size.height()-50);
//    m_size.setWidth(m_size.width()-50);
//    this->resize(size - QSize(0, 0));
//    makeGridRect();
//}

void GameBoardWidget::drawBoard(QPainter *painter) {
    int w = this->size().width();
    int h = this->size().height();
    int lim = w > h ? h : w;
//    qDebug() << "lim: " << lim;
    lim = lim - (m_boardBorder*2);
    QImage scaledboard = m_woodImg.scaledToHeight(lim);
//    qDebug() << scaledboard.size();
    painter->drawImage(m_boardBorder, m_boardBorder , scaledboard, 0, 0, lim, lim);
    painter->setPen(QPen(QColor(0,0,0,200), 2));
    painter->drawRect(m_boardBorder, m_boardBorder, lim, lim);

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
    const quint32 psize = gridSpace * 0.75;
//    const quint32 imgWidth = m_blackImg.size().width();
//    const quint32 imgHeight = m_blackImg.size().height();
    QImage scaled;
    const quint32 imgWidth = psize, imgHeight = psize;
    for (int j = 0; j < m_board->getSize().height(); j++) {
        for (int k = 0; k < m_board->getSize().width(); k++) {
            const BoardMatrix::StateFlag flag = m_board->value(j, k);
            int x = ((gridSpace*j)-(imgWidth/2))+m_gridRect.x();
            int y = ((gridSpace*k)-(imgHeight/2))+m_gridRect.y();
            switch(flag) {
                case BoardMatrix::BlackPiece:
                    scaled = m_blackImg.scaledToHeight(psize, Qt::SmoothTransformation);
                    painter->drawImage(x, y, scaled);
                    break;
                case BoardMatrix::WhitePiece:
                    scaled = m_whiteImg.scaledToHeight(psize, Qt::SmoothTransformation);
                    painter->drawImage(x, y, scaled);
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

    if (gridSpace*m_bx < gridSpace*m_gridSize) {
        QRect vrect(m_gridRect.x()+(gridSpace*m_bx)-(m_highlightWidth/2),
                    m_gridRect.y(), m_highlightWidth, m_gridRect.height());
        if (vrect.x() < m_gridRect.x()) {
            vrect.setX(m_gridRect.x()+1);
            vrect.setWidth(m_highlightWidth);
        }
        painter->drawRect(vrect);
    }

    if (gridSpace*m_by < gridSpace*m_gridSize) {
        QRect hrect(m_gridRect.x(), m_gridRect.y()+(gridSpace*m_by)-(m_highlightWidth/2),
                    m_gridRect.width(), m_highlightWidth);
        if (hrect.y() < m_gridRect.y()) {
            hrect.setY(m_gridRect.y()+1);
            hrect.setHeight(m_highlightWidth);
        }
        painter->drawRect(hrect);
    }
}

quint32 GameBoardWidget::getGridSpace() const {
    quint32 s = m_gridRect.width() / (m_gridSize-1);
    return s;
}

void GameBoardWidget::makeGridRect() {
    int w = this->size().width();
    int h = this->size().height();
    int lim = w > h ? h : w;
    int dim = lim;
//    int difMod = dim % (m_gridSize-1);
    dim = dim - (m_gridBorder*2);
//    qDebug() << "dim: " << dim << " difMod: " << difMod << " bborder: " << m_boardBorder;
    m_gridRect = QRect(m_gridBorder,m_gridBorder, dim, dim);
//    qDebug() << m_gridRect;
}
