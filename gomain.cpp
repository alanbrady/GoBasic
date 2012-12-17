#include "gomain.h"
#include "ui_gomain.h"

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>

GoMain::GoMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoMain)
{
    ui->setupUi(this);
//    this->setFixedSize(700, 600);
    QRect geom = this->geometry();
    geom.setWidth(700);
    geom.setHeight(500);
    this->setGeometry(geom);

    centralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);

    board = new BoardMatrix(9, 9);
    p1 = new HumanPlayer("Bob", logic, AbstractPlayer::WHITE, this);
    p2 = new HumanPlayer("Jim", logic, AbstractPlayer::BLACK, this);
    logic = new GameLogic(board, p1, p2);

    gb = new GameBoardWidget(centralWidget, board, 9);
    gameui = new GameUI(this);
    gameui->setMinimumWidth(300);
    gameui->setMaximumWidth(300);
    mainLayout->addWidget(gb);
    mainLayout->addWidget(gameui);

    connect(gb, SIGNAL(clicked()), this, SLOT(boardClicked()));
}

GoMain::~GoMain()
{
    delete ui;
    delete board;
    delete logic;
}

//void GoMain::resizeEvent(QResizeEvent * newSize) {
//    gb->sizeChanged(newSize->size());
//}

void GoMain::boardClicked() {
    if (logic->getActivePlayer()->isHuman()) {
        logic->playerMove(gb->getBoardX(), gb->getBoardY());
    }
    gb->repaint();
}
