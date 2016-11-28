#include "bullet.h"

Bullet::Bullet(double pointCentralX, double pointCentralY, double xabscisse, double yordonne, double xdirection, double ydirection)
{
    this->setPointX(pointCentralX);
    this->setPointY(pointCentralY);
    this->setDirectionX(xdirection);
    this->setDirectionY(ydirection);
    this->setX_abscisse(xabscisse);
    this->setY_ordonne(yordonne);


    bulletLine.setLine(pointX, pointY, directionX, directionY);
}

QLine Bullet::getBulletLine() const
{
    return bulletLine;
}

void Bullet::setBulletLine(const QLine &value)
{
    bulletLine = value;
}

void Bullet::checkCollision()
{

}

double Bullet::getDirectionY() const
{
    return directionY;
}

void Bullet::setDirectionY(double value)
{
    directionY = value;
}

double Bullet::getDirectionX() const
{
    return directionX;
}

void Bullet::setDirectionX(double value)
{
    directionX = value;
}

double Bullet::getPointY() const
{
    return pointY;
}

void Bullet::setPointY(double value)
{
    pointY = value;
}

double Bullet::getPointX() const
{
    return pointX;
}

void Bullet::setPointX(double value)
{
    pointX = value;
}

double Bullet::getY_ordonne() const
{
    return y_ordonne;
}

void Bullet::setY_ordonne(double value)
{
    y_ordonne = value;
}

double Bullet::getX_abscisse() const
{
    return x_abscisse;
}

void Bullet::setX_abscisse(double value)
{
    x_abscisse = value;
}

