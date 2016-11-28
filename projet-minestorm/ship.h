#ifndef SHIP_H
#define SHIP_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <QPoint>
#include <QBrush>
#include <vector>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <QDebug>
#include "box.h"
#include "bullet.h"
#include "mine.h"
#include <QString>
#include "explosion.h"
#include <QSharedPointer>
#include <QObject>

using namespace std;
class Ship : public QObject
{
    Q_OBJECT
public:

    Ship();
    void setShipFire(const vector<Bullet> &value);
    void fire();
    void acceleration();
    void hited();
    void move(QSize size);
    bool checkCollision(QPolygon poly);
    void draw(QPainter &painter);
    void drawBullet(QPainter &painter, QSize size, vector<QSharedPointer<Mine> > &_mines, vector<Explosion> &_explosions);

    QLine getShipLine() const;
    void setShipLine(const QLine &value);
    int getLife() const;
    void setLife(int value);
    double getCurrentSpeed() const;
    void setCurrentSpeed(double value);
    int getLastEcart_dx() const;
    void setLastEcart_dx(int value);
    int getLastEcart_dy() const;
    void setLastEcart_dy(int value);
    float getAngle() const;
    void setAngle(float value);
    float getRadiant() const;
    void setRadiant(float value);
    void rotateLeft();
    void rotateRight();
    Box box() const;
    void setBox(const Box &box);
    vector<Bullet> getShipFire() const;
    double getScoreFrame() const;
    void setScoreFrame(double value);
    bool getImmune() const;
    void setImmune(bool value);

private slots:
    void shotSignal();
    void immunity();
private:
    bool immune = false;
    int compteurTimer = 0;
    int nbShot = 0;
    int life = 4;
    float radiant = 0;
    float angle = 20;
    int size = 30;
    int lastEcart_dx = 0;
    int lastEcart_dy = 0;
    int rotation = 0;
    double currentSpeed = 0;
    double scoreFrame = 0;
    void createCollisionBox(); // creation de la box de collision
    void updatePositionBox(); // Déplacement de la box de collision après chaque déplacements
    void respawn(); // Fonction de respawn
    QSharedPointer<QTimer> _timer; // QTimer pour les 4 tirs par secondes
    QSharedPointer<QTimer> _timerRespawn; // QTimer pour l'invulnérabilité après une collision
    QList<QSharedPointer<Mine>> mines_to_be_deleted; // QList de mine à delete après une collision
    QPixmap pixmap; // Déclaration pixmap du vaisseau
    QString path = ":/Assets/Assets/ship.png"; // Path pour l'image du vaisseau
    QLine shipLine; // Line pour le vaisseau
    Box _box; // Box du vaisseau
    vector<Bullet> shipFire; // Tirs du vaisseau


};

#endif // SHIP_H
