#include "gomain.h"
#include "ui_gomain.h"

#include <QWidget>
#include <QDebug>
#include <QString>

GoMain::GoMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoMain)
{
    ui->setupUi(this);
    this->setFixedSize(500, 500);

    board = new BoardMatrix(9, 9);
    gb = new GameBoardWidget(this, board, this->size());
    logic = new GameLogic(board);
    logic->checkCaptures(BoardMatrix::BlackPiece);
}

GoMain::~GoMain()
{
    delete ui;
    delete board;
    delete logic;
}

void GoMain::resizeEvent(QResizeEvent * newSize) {
//    quint32 height = newSize->size().height();
//    quint32 width = newSize->size().width();
//    quint32 longest = height > width ? height : width;
//    longest -= 1;
//    qDebug() << "Longest: " << longest;
//    QSize squareSize = QSize(longest, longest);
//    qDebug() << "squareSize: " << squareSize << " newSize: " << newSize->size();
//    if (squareSize != newSize->size())
//        this->resize(longest, longest);
    gb->sizeChanged(newSize->size());
}
