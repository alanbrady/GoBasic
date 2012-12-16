#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QImage>

class GameUI : public QWidget
{
    Q_OBJECT
public:
    explicit GameUI(QWidget *parent = 0);
    virtual ~GameUI();

    const static char* BackgroundImagePath;

signals:
    void clicked();

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    int heightForWidth(int w) const { return w; }

private:
    QImage* m_background;
    void drawBackground(QPainter* painter);
    
};

#endif // GAMEUI_H
