#ifndef ZIPPEDBUFFERPOOL_H
#define ZIPPEDBUFFERPOOL_H

#include "zippedbuffer.h"
#include <list>
#include <QPair>
#include <QList>
#include <QDebug>
#include <QWaitCondition>
#include <QMutexLocker>
class ZippedBufferPool
{
public:
    ZippedBufferPool(QWaitCondition *condition);
    void put(const ZippedBuffer &zb);
    QPair<bool, ZippedBuffer> tryGet();
    int count();
    void done();
    bool getDone();
private:
    QList<ZippedBuffer> m_buffer;
    bool m_done;
    QWaitCondition *m_condition;
    bool isAwake;
    QMutex mutex;
};

#endif // ZIPPEDBUFFERPOOL_H
