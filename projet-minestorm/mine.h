#ifndef MINE_H
#define MINE_H
#include <QPoint>
#include <QBrush>
#include <vector>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <QDebug>
#include "box.h"
#include <QObject>
#include <QTimer>
#include <QSharedPointer>

using namespace std;
class Mine : public QObject
{
    Q_OBJECT
public:
    Mine(QPoint point, double size, int timerLenght);
    QPoint point() const;
    void setPoint(const QPoint &point);
    Box box() const;
    void setBox(const Box &box);
    double size() const;
    void setSize(double size);
    QLine getDirectionLine() const;
    void setDirectionLine(const QLine &value);
    QPoint newPoint() const;
    void setNewPoint(const QPoint &newPoint);
    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);
    void draw(QPainter &painter);
    void move(QSize size);
    void updatePositionBox();
    bool checkCollision(QPoint bulletPoint);
    double getCompteur() const;
    void setCompteur(double value);

    bool getIsEclosion() const;
    void setIsEclosion(bool value);

    QSharedPointer<QTimer> timer() const;
    void setTimer(const QSharedPointer<QTimer> &timer);

private slots:
    void eclosion();
private:
    void createCollisionBox();
    int angle;
    double _size;
    QImage _image;
    QSharedPointer<QTimer> _timer;
    Box _box;
    QPoint _point;
    QPoint _newPoint;
    QLine directionLine;
    QString path = ":/Assets/Assets/point-minestorm.png";
    QString pathEvolved = "/home/epsi/minestorm/Assets/evolution.png";
    QPixmap pixmap;
    double compteur;
    bool isEclosion = false;
};

#endif // MINE_H
