#include "picture.h"
#include <QDebug>

Picture::Picture()
{
}

QString Picture::getEncodedPictureInString(){
    QFile* file = new QFile("/home/epsi/Documents/Projet-embarque/remote-app-on-raspberry/assets/raspberry-pi-logo.png");
    file->open(QIODevice::ReadOnly);
    QByteArray image = file->readAll();
    QString encoded = QString(image.toBase64());
    return encoded;
}

void Picture::takePicture(){
    system("raspistill -v -o /home/pi/app-picture.jpg");
}
