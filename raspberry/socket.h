#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpSocket>
#include <QObject>


class Socket : public QObject
{
    Q_OBJECT
public:

    Socket();
    explicit Socket(QTcpSocket *m_socket, QObject *parent = 0);
    QByteArray packMessage(const QString &msg) const;
    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);

signals:
    void receiveMessage(const QString &msg);
    void socketDisconnected();
public slots:
    void readData();
    void disconnected();

private:
    quint16 _msgSize;
    QTcpSocket *m_socket;

};

#endif // SOCKET_H
