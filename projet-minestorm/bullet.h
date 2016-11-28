#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QBrush>
#include <vector>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <QDebug>

using namespace std;

class Bullet
{
public:
    Bullet(double pointCentralX, double pointCentralY, double xabscisse, double yordonne, double xdirection, double ydirection);
public:

    double getX_abscisse() const;
    void setX_abscisse(double value);

    double getY_ordonne() const;
    void setY_ordonne(double value);

    double getPointX() const;
    void setPointX(double value);

    double getPointY() const;
    void setPointY(double value);

    double getDirectionX() const;
    void setDirectionX(double value);

    double getDirectionY() const;
    void setDirectionY(double value);

    QLine getBulletLine() const;
    void setBulletLine(const QLine &value);

    void checkCollision();

private:
    QLine bulletLine;
    double pointX;
    double pointY;
    double directionX;
    double directionY;
    double x_abscisse;
    double y_ordonne;

protected:
};

#endif // BULLET_H
