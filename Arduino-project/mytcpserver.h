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



class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void launchConnector();

    Socket *getSocket() const;
    void setSocket(Socket *value);

private:
    QTcpServer *server;
    Socket *socket;

public slots:
    void newConnection();

private slots:
    void messageDispatcher(const QString &msg);

};



#endif // MYTCPSERVER_H
