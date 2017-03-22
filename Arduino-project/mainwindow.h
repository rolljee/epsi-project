#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"
#include "sqlconnexion.h"
#include "socket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MyTcpServer *server, Sqlconnexion *connector, QWidget *parent = 0);
    ~MainWindow();
    MyTcpServer *m_serv;
    Socket *m_socket;
    Sqlconnexion *m_connector;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
