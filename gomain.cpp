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
    p1 = new HumanPlayer(logic, AbstractPlayer::WHITE, this);
    p2 = new HumanPlayer(logic, AbstractPlayer::BLACK, this);
    logic = new GameLogic(board, p1, p2);
    gb = new GameBoardWidget(this, board, this->size());

    connect(gb, SIGNAL(clicked()), this, SLOT(boardClicked()));
}

GoMain::~GoMain()
{
    delete ui;
    delete board;
    delete logic;
}

void GoMain::resizeEvent(QResizeEvent * newSize) {
    gb->sizeChanged(newSize->size());
}

void GoMain::boardClicked() {
    if (logic->getActivePlayer()->isHuman()) {
        logic->playerMove(gb->getBoardX(), gb->getBoardY());
    }
    gb->repaint();
}
