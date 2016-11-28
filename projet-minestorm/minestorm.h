#  ifndef MINESTORM_H
#define MINESTORM_H
#include "game.h"
#include "bullet.h"
#include "ship.h"
#include "explosion.h"

#include <QPoint>
#include <QBrush>
#include <vector>
#include <QVector>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <QDebug>
#include <QLabel>
#include <string>
#include "threadbullet.h"



using namespace std;
/**
 * @brief La classe Minestorm correspond au Mini-Projet à rendre pour le 14 Février
 */

class Minestorm : public Game
{
public:
    Minestorm(const QSize &size,QObject *parent = nullptr);
    virtual void draw(QPainter &painter, QRect &rect) override;
    void mousePressed( int x, int y) override;
    void keyPressed( int key ) override;
    void keyReleased( int key ) override;
    void mouseReleased( int x, int y) override;
    void mouseMoved(int x, int y) override;

private:
    virtual void step() override ;
    void initialize() override;
    void addMines(QPoint point, double size, int timerLenght);
    void goDown();
    void initMine();
    vector<QSharedPointer<Mine>> _mines;
    QList<QSharedPointer<Mine>> mines_to_be_deleted;
    vector<Explosion> _explosions;
    Ship myShip;
    QFont font;
};
#endif // MINESTORM_H
