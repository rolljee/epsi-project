#include <QCoreApplication>
#include <QApplication>
#include "mytcpserver.h"
#include "mainwindow.h"
#include "sqlconnexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTcpServer server;
    Sqlconnexion connector;
    MainWindow w(&server, &connector);
    w.show();
    return a.exec();
}
