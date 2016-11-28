#include "zippedbuffer.h"

ZippedBuffer::ZippedBuffer()
{

}
ZippedBuffer::ZippedBuffer(const QString &filename, const QByteArray &data):
    m_FileName(filename), m_data(data)
{
}
void ZippedBuffer::write(QDataStream &stream) const
{
    stream << m_FileName;
    stream << m_data;
}
void ZippedBuffer::read(QDataStream &stream)
{
    stream >> m_FileName;
    stream >> m_data;
}
const QString &ZippedBuffer::get_filename() const
{
    return m_FileName;
}

const QByteArray &ZippedBuffer::get_data() const
{
    return m_data;
}

