#ifndef EPSIFILECOMPRESSOR_H
#define EPSIFILECOMPRESSOR_H
#include <QString>
#include <QList>
#include <QSharedPointer>
#include "filepool.h"
#include "zippedbufferpool.h"
#include "zipper.h"
#include "writer.h"
#include <QWaitCondition>
#include <QMutex>
#include <QFileInfo>

class EpsiFileCompressor
{
public:
    EpsiFileCompressor();
    EpsiFileCompressor(const int nbThread);
    void compress(const QString &folder, const QString &ecfFileName);
    void uncompress(const QString &ecfFileName, const QString &folder );
private:
    int m_nbThread;
    QWaitCondition m_waitCondition;
};

#endif // EPSIFILECOMPRESSOR_H
