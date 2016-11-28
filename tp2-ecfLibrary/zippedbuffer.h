#ifndef ZIPPEDBUFFER_H
#define ZIPPEDBUFFER_H

#include <QString>
#include <QDataStream>
#include <QByteArray>

class ZippedBuffer
{
public:
    ZippedBuffer();
    ZippedBuffer(const QString &filename, const QByteArray &data);
    void write(QDataStream &stream) const;
    void read(QDataStream &stream);

    const QString &get_filename() const;
    const QByteArray &get_data() const;

private:
    QString m_FileName;
    QByteArray m_data;
};

#endif // ZIPPEDBUFFER_H
