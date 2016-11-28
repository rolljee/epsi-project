#include "explosion.h"
#include <QFont>

Explosion::Explosion(QPoint point){
    _point = point;
    pen.setColor(Qt::GlobalColor::red);
    pen.setWidth(3);
    for (int i = 0; i <= 15; ++i) {
        angle = -7 + (rand() %(int)(7 - (-7) +1 ));
        randValue = (rand() %(int)(1 - (-5) +1 ));
        line.setPoints(_point,QPoint(_point.x() + randValue * cos(angle),_point.y() + randValue * sin(angle)));
        explo.append(line);
    }
}

void Explosion::draw(QPainter &painter){
    for(int j = 0; j < explo.size(); j++){
        painter.setPen(pen);
        painter.drawLine(explo.at(j));
        if (compteur < 100) {
            QLine myLine = explo[j].translated(explo[j].dx()/2,explo[j].dy()/2);
            explo[j].setP2(myLine.p2());
            ++compteur;
        }else {
            auto _p1 = -explo[j].dx()/2;
            auto _p2 = -explo[j].dy()/2;
            QLine myLine = explo[j].translated(_p1,_p2);
            explo[j].setP2(myLine.p2());
            if (_p1 == _p2) {
                explo.removeAt(j);
            }
        }
    }
}
