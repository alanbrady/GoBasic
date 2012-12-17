#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QImage>
#include <QRect>
#include "abstractplayer.h"

class GameUI : public QWidget
{
    Q_OBJECT
public:
    explicit GameUI(QWidget *parent = 0);
    virtual ~GameUI();

    const static char* BackgroundImagePath;
    const static char* PlayerTextPath;
    const static char* PlayerTextBlackPath;
    const static char* PlayerTextWhitePath;
    const static char* PassTextPath;

signals:
    void clicked();

public slots:
    void playerChanged(AbstractPlayer* p);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    int heightForWidth(int w) const { return w; }

private:
    QImage m_background;
    QImage m_playertext;
    QImage m_playertextblack;
    QImage m_playertextwhite;
    QImage m_passtext;
    AbstractPlayer *m_activeplayer;
    void drawBackground(QPainter* painter);
    void drawPlayerText(QPainter* painter);
    void drawPlayerColor(QPainter* painter);
    void drawPass(QPainter* painter);
    const QRect getPlayerTextRect() const;
    const QRect getPlayerColorRect() const;
    const QRect getPassRect() const;
    
};

#endif // GAMEUI_H
