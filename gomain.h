#ifndef GOMAIN_H
#define GOMAIN_H

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "gameboardwidget.h"
#include "boardmatrix.h"
#include "gamelogic.h"
#include "humanplayer.h"

namespace Ui {
    class GoMain;
}

class GoMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit GoMain(QWidget *parent = 0);
    ~GoMain();

public slots:
    void boardClicked();

protected:
//    void resizeEvent(QResizeEvent * newSize);

private:
    Ui::GoMain *ui;
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    GameBoardWidget *gb;
    BoardMatrix *board;
    GameLogic *logic;
    HumanPlayer *p1;
    HumanPlayer *p2;

};

#endif // GOMAIN_H
