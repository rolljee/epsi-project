#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MyTcpServer *server, Sqlconnexion *connector, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    m_serv(server),
    m_connector(connector)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
