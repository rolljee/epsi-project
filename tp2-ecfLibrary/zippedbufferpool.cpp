#include "zippedbufferpool.h"

ZippedBufferPool::ZippedBufferPool(QWaitCondition *condition)
    :m_done(false),
      m_condition(condition),
      isAwake(false)
{
}
void ZippedBufferPool::done(){

    QMutexLocker locker(&mutex);
    m_done = true;
}

bool ZippedBufferPool::getDone(){

    QMutexLocker locker(&mutex);
    return m_done;
}
void ZippedBufferPool::put(const ZippedBuffer &zb){

    QMutexLocker locker(&mutex);
    m_buffer.push_back(zb);
    if (!isAwake) {
        m_condition->wakeAll();
        isAwake = true;
    }
    qDebug() << "ZippedBufferPool::put()" << m_buffer.count() << endl;
}
QPair<bool,ZippedBuffer> ZippedBufferPool::tryGet(){

    QMutexLocker locker(&mutex);
    if( m_buffer.empty()) {
        return QPair<bool, ZippedBuffer>(false,ZippedBuffer());
    }
    auto buffer = m_buffer.front();
    m_buffer.pop_front();
    return QPair<bool,ZippedBuffer>(true, buffer);
}
int ZippedBufferPool::count() {

    return m_buffer.size();
}
