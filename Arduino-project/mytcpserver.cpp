#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    launchConnector();
}

void MyTcpServer::launchConnector(){
    connect(server, SIGNAL(newConnection()),this, SLOT(newConnection()));
    !server->listen(QHostAddress::Any, 4242) ? qDebug() << "Server could not start" : qDebug() << "Server started!";
}
Socket *MyTcpServer::getSocket() const
{
    return socket;
}

void MyTcpServer::setSocket(Socket *value)
{
    socket = value;
}

void MyTcpServer::newConnection(){
    qDebug() << "MyTcpServer::newConnection()";
    socket = new Socket(server->nextPendingConnection());
    connect(socket,SIGNAL(receiveMessage(QString)),this,SLOT(messageDispatcher(QString)));
}


void MyTcpServer::messageDispatcher(const QString &msg){
    qDebug() << "MessageDispatcher2()" << msg.length();
    qDebug() << "MessageDispatcher()" << msg;
}
