#include "gameui.h"
#include <QPainter>
#include <QImage>

const char* GameUI::BackgroundImagePath = "./woodframe.png";

GameUI::GameUI(QWidget *parent) :
    QWidget(parent)
{
    m_background = new QImage(BackgroundImagePath);
}

GameUI::~GameUI() {
    delete m_background;
}

void GameUI::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    this->drawBackground(&painter);

    painter.drawRect(0,0,this->size().width()-1, this->size().height()-1);
}

void GameUI::mousePressEvent(QMouseEvent *) {
    emit clicked();
}

void GameUI::drawBackground(QPainter* painter) {
    painter->drawImage(0,0,(*m_background));
}

