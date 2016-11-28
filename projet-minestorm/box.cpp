#include "box.h"


Box::Box()
{
}
Box::Box(QRect rect)
{
    polygon = QPolygon(rect,false);
}
QPolygon Box::getPolygon() const
{
    return polygon;
}

void Box::setPolygon(const QPolygon &value)
{
    polygon = value;
}
