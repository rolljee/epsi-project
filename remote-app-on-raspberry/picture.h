#ifndef PICTURE_H
#define PICTURE_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QPixmap>
#include "raspicam/raspicam.h"
#include <QDataStream>

class Picture
{
public:
    Picture();
    QString getEncodedPictureInString();
    void takePicture();
};

#endif // PICTURE_H
