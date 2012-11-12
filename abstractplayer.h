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

    AbstractPlayer(GameLogic* logic, Color color, QObject* parent = 0);
    virtual ~AbstractPlayer() {}

    const Color color() const { return m_color; }
    void startTurn();

    virtual void doTurn() = 0;
    virtual const bool isHuman() const { return false; }

public slots:
    bool doMove(int x, int y);

private:
    GameLogic* m_logic;
    Color m_color;
    bool m_isActive;
    int m_points;
    QString m_name;

};




#endif // ABSTRACTPLAYER_H
