// mytcpserver.cpp

#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    launchConnector();
}

void MyTcpServer::launchConnector(){
    connect(server, SIGNAL(newConnection()),this, SLOT(newConnection()));
    !server->listen(QHostAddress::Any, 9999) ? qDebug() << "Server could not start" : qDebug() << "Server started!";
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
    Worker *worker = new Worker();
    worker->start();
    socket->moveToThread(worker);
    connect(socket,SIGNAL(receiveMessage(QString)),this,SLOT(messageDispatcher(QString)));
}

void MyTcpServer::messageDispatcher(const QString &msg){
    if (msg.length() < 200) {
        emit code(msg);
    }else {
        QImage image;
        QPixmap pix;
        QByteArray ba = base64_decode(msg);
        qDebug() << ba;
        image.loadFromData(ba, "PNG");
        qDebug() << image;
        pix = pix.fromImage(image);
        QPixmap decodedPicture = pix.scaled(QSize(300,350),  Qt::KeepAspectRatio);
        emit picture(decodedPicture);
    }
}
QByteArray MyTcpServer::base64_decode(QString picture){
    qDebug() << picture;
    QByteArray ba;
    ba.append(picture);
    return QByteArray::fromBase64(ba);
}


