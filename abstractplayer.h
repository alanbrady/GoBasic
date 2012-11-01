#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include <QObject>

class GameLogic;

class AbstractPlayer : public QObject
{
    Q_OBJECT
public:
    enum Color {
        WHITE,
        BLACK
    };

    AbstractPlayer(GameLogic* log, Color color, QObject* parent = 0);
    virtual ~AbstractPlayer() {}

    virtual void startTurn() = 0;
    virtual bool isHuman() { return false; }
    Color color() const { return m_color; }

public slots:
    bool doMove(int x, int y);

private:
    GameLogic* m_logic;
    Color m_color;

};




#endif // ABSTRACTPLAYER_H
