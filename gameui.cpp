#include "gameui.h"
#include <QPainter>
#include <QImage>

#include <QDebug>

const char* GameUI::BackgroundImagePath = "./woodframe.png";
const char* GameUI::PlayerTextPath = "player.png";
const char* GameUI::PlayerTextBlackPath = "player_black.png";
const char* GameUI::PlayerTextWhitePath = "player_white.png";
const char* GameUI::PassTextPath = "pass.png";

GameUI::GameUI(QWidget *parent) :
    QWidget(parent),
    m_activeplayer(0)
{
    m_background.load(BackgroundImagePath);
    m_playertext.load(PlayerTextPath);
    m_playertextblack.load(PlayerTextBlackPath);
    m_playertextwhite.load(PlayerTextWhitePath);
    m_passtext.load(PassTextPath);
}

GameUI::~GameUI() {
}

void GameUI::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    this->drawBackground(&painter);
    this->drawPlayerText(&painter);
    this->drawPlayerColor(&painter);

    painter.drawRect(0,0,this->size().width()-1, this->size().height()-1);
}

void GameUI::mousePressEvent(QMouseEvent *) {
    emit clicked();
}

void GameUI::drawBackground(QPainter* painter) {
    painter->drawImage(0,0,m_background);
}

void GameUI::drawPlayerText(QPainter *painter) {
    painter->drawImage(getPlayerTextRect(), m_playertext);
}

void GameUI::drawPlayerColor(QPainter *painter) {
    if (m_activeplayer != 0) {
        if (m_activeplayer->color() == AbstractPlayer::BLACK) {
            painter->drawImage(getPlayerColorRect(), m_playertextblack);
        } else if (m_activeplayer->color() == AbstractPlayer::WHITE) {
            painter->drawImage(getPlayerColorRect(), m_playertextwhite);
        }
    }
}

void GameUI::drawPass(QPainter *painter) {
}

const QRect GameUI::getPlayerTextRect() const {
    int wigwid = this->size().width();
    int imgwid = m_playertext.width();
    QRect rect;
    rect.setX((wigwid-imgwid)/2);
    rect.setY(50);
    rect.setWidth(imgwid);
    rect.setHeight(m_playertext.height());
//    qDebug() << rect;
    return rect;
}

const QRect GameUI::getPlayerColorRect() const {
    int wigwid = this->size().width();
    int imgwid = m_playertextblack.width();
    QRect rect = m_playertextblack.rect();
    rect.moveLeft((wigwid-imgwid)/2);
    rect.moveTop(90);
    qDebug() << rect;
    return rect;
}

const QRect GameUI::getPassRect() const {
}

void GameUI::playerChanged(AbstractPlayer *p) {
    m_activeplayer = p;
    repaint();
}

