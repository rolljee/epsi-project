#include "socket.h"

Socket::Socket(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    _msgSize(0),
    m_socket(socket)
{
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(m_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
}

void Socket::readData() {
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_0);
    if (_msgSize == 0){
        in >> _msgSize;
    }
    QString message;
    in >> message;
    _msgSize = 0;
    qDebug() << "readData()" << message;
    emit receiveMessage(message);
}

QByteArray Socket::packMessage(const QString &msg) const {
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint16) 0;
    out << msg;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    return  block;
}
void Socket::disconnected(){
    emit socketDisconnected();
}
QTcpSocket *Socket::getSocket() const {
    return m_socket;
}

void Socket::setSocket(QTcpSocket *value) {
    m_socket = value;
}

