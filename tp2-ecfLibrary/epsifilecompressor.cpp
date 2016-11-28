#include "epsifilecompressor.h"

EpsiFileCompressor::EpsiFileCompressor()
{
}

EpsiFileCompressor::EpsiFileCompressor(const int nbThread)
    : m_nbThread(nbThread)
{
}

void EpsiFileCompressor::compress(const QString &folder, const QString &ecfFileName)
{
    FilePool pool(folder);
    ZippedBufferPool bufferPool(&m_waitCondition);
    QList<QSharedPointer<Zipper>> zippers;

    for(int i = 0; i < m_nbThread; ++i) {
        zippers.push_back(QSharedPointer<Zipper>(new Zipper(&pool, &bufferPool)));
        zippers.back()->start();
    }

    auto writer = new Writer(&bufferPool,ecfFileName,&m_waitCondition);
    writer->start();

    for (QSharedPointer<Zipper> &zipper : zippers) {
        zipper->wait();
    }
    bufferPool.done();
    writer->wait();
    qDebug() << "Programme ended !";

}

void EpsiFileCompressor::uncompress(const QString &ecfFileName, const QString &folder)
{
    qDebug() << "ecfFIleName -->" << ecfFileName << endl;
    qDebug() << "&folder --> " << folder << endl;
    QString filename;
    QByteArray compressedData;
    QFile fileToUncompress(ecfFileName);
    fileToUncompress.open(QIODevice::ReadOnly);
    QByteArray byteArray(fileToUncompress.readAll());
    QDataStream dataStream(byteArray);
    while (!dataStream.atEnd()) {
        dataStream >> filename >> compressedData;
        QStringList splitted_fileName = filename.split("/");
        QFile file(folder+"/"+splitted_fileName.back());
        file.open(QIODevice::WriteOnly);
        file.write(qUncompress(compressedData));
    }
    qDebug() << "Writed ended !" << endl;
}
