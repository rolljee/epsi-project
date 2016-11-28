#include "threadbullet.h"

ThreadBullet::ThreadBullet()
{
    qDebug() << "Constructeur du Thread";
}

void ThreadBullet::run()
{
    qDebug() << "thread::run()" << isRunning();
    exec();
}

void ThreadBullet::callShot()
{
    qDebug() << "Shot fired";
    _ptrShip->fire();
}

void ThreadBullet::setPtrShip(Ship *ptrShip)
{
    _ptrShip = ptrShip;
}

