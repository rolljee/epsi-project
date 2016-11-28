#include "zipper.h"

Zipper::Zipper()
{
}

Zipper::Zipper(FilePool *pool, ZippedBufferPool *bufferPool)
    : m_buffer_pool(bufferPool),
      m_pool(pool)
{
}
void Zipper::run(){

    QString filename;
    filename = m_pool->tryGetFile();
    while(filename != "") {
        processFile(filename);
        filename = m_pool->tryGetFile();
    }
}

void Zipper::processFile(const QString &filename) {

    QFile file(filename);
    if( file.open(QFile::ReadOnly) == true) {
        compress(file);
    }
}
void Zipper::compress(QFile &file){

    compressed_file = qCompress(file.readAll());
    sendFile(compressed_file,file.fileName());
}


void Zipper::sendFile(const QByteArray &array, const QString &fileName){

    ZippedBuffer zb(fileName,array);
    m_buffer_pool->put(zb);
}
