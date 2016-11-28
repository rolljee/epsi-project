#ifndef BOX_H
#define BOX_H
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QBrush>
#include <vector>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <QDebug>

using namespace std;

class Box
{
public:
    Box();
    Box(QRect rect);
    QPolygon getPolygon() const;
    void setPolygon(const QPolygon &value);

private:
    QPolygon polygon;
};

#endif // BOX_H
