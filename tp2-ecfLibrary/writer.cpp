#include "writer.h"

Writer::Writer()
{
}

Writer::Writer(ZippedBufferPool *bufferPool, const QString destFile, QWaitCondition *condition)
    : m_zipped_pool(bufferPool),
      m_fileDest(destFile),
      m_condition(condition)
{
    m_fileDest.open(QIODevice::WriteOnly);
    m_dataStream.setDevice(&m_fileDest);
    qDebug() << "Contructor writer";
}

void Writer::run(){

    m_condition->wait(&mutex);
    QPair<bool,ZippedBuffer> zippedBuffer;
    zippedBuffer = m_zipped_pool->tryGet();

    while( !m_zipped_pool->getDone() || zippedBuffer.first) {
        if (zippedBuffer.first) {
            processFile(zippedBuffer.second);
        }

        zippedBuffer = m_zipped_pool->tryGet();
    }
}

void Writer::processFile(const ZippedBuffer &zipped) {
    qDebug() << "File --> " << zipped.get_filename();
   m_dataStream << zipped.get_filename() << zipped.get_data();
}


