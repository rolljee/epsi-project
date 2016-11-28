#ifndef WRITER_H
#define WRITER_H
#include <QThread>
#include <QString>
#include <QFile>
#include <QWaitCondition>
#include <QMutex>
#include <QDataStream>
#include "zippedbufferpool.h"
#include "zippedbuffer.h"

class Writer : public QThread
{
public:
    Writer();
    Writer(ZippedBufferPool *bufferPool, const QString destFile, QWaitCondition *condition);
    void run() override;
    void processFile(const ZippedBuffer &zipped);
private:
    ZippedBufferPool *m_zipped_pool;
    QFile m_fileDest;
    QWaitCondition *m_condition;
    QMutex mutex;
    QDataStream m_dataStream;
};

#endif // WRITER_H
