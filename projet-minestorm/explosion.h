#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QPoint>
#include <iostream>
#include <QDebug>
#include <vector>
#include <QPainter>

class Explosion
{
public:
    Explosion(QPoint point);
    void draw(QPainter &painter);
private:
    QPen pen;
    int compteur = 0;
    QPoint _point;
    QLine line;
    int randValue = 0;
    int angle = 0;
    QList<QLine> explo;
};

#endif // EXPLOSION_H
