#ifndef WORKER_H
#define WORKER_H
#include <QThread>
#include "socket.h"

class Worker : public QThread
{
public:
    Worker();
protected:
    void run();
};

#endif // WORKER_H
