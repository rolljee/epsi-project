#ifndef ZIPPER_H
#define ZIPPER_H
#include <QThread>
#include <QString>
#include <QFile>
#include <zippedbuffer.h>
#include <zippedbufferpool.h>
#include <QSharedPointer>
#include <filepool.h>

class Zipper : public QThread
{
public:
    Zipper();
    Zipper(FilePool *pool,ZippedBufferPool *bufferPool);
    void run() override;
    void compress(QFile &file);
    void processFile(const QString &filename);
    void sendFile(const QByteArray &array, const QString &fileName);
private:
    QByteArray compressed_file;
    ZippedBufferPool *m_buffer_pool;
    FilePool *m_pool;
};

#endif // ZIPPER_H
