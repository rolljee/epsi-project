#include "worker.h"
#include "QDebug"


Worker::Worker()
{
}
void Worker::run(){
    exec();
    qDebug() << "Worker launched";
}
