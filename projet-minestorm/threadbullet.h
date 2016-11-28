#ifndef THREADBULLET_H
#define THREADBULLET_H
#include <QThread>
#include <QDebug>
#include <QKeyEvent>
#include "ship.h"
class ThreadBullet : public QThread
{
public:
    ThreadBullet();
    void run();
    void callShot();

    void setPtrShip(Ship *ptrShip);
private:
    Ship *_ptrShip;

};

#endif // THREADBULLET_H
