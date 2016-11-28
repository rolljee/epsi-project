#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include "socket.h"
#include "worker.h"



class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void launchConnector();

    Socket *getSocket() const;
    void setSocket(Socket *value);
    QByteArray base64_decode(QString picture);

private:
    QTcpServer *server;
    Socket *socket;

signals:
    void code(const QString code);
    void picture(const QPixmap decodedPicture);

public slots:
    void newConnection();
private slots:
    void messageDispatcher(const QString &msg);

};

#endif // MYTCPSERVER_H
