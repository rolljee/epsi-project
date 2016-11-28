#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
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

private:
    Ui::MainWindow *ui;
    MyTcpServer *m_serv;
    Socket *m_socket;
    Sqlconnexion *m_connector;

signals:
    void getBddPicture(const QString msg);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void decode_code(const QString code);
    void decode_picture(QPixmap picture);
    void decode_picture_bdd(const QString code);
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
