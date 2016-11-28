#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
#include "picture.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QByteArray packMessage(const QString &msg) const;
    void launchConnexion();

    Ui::MainWindow *ui;
    QTcpSocket *socket;
    Picture *pic;
    int _bytes;
private:
    quint16 _msgSize;
    bool onErrorState = false;
signals:
    void receiveMessage(const QString &msg);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void readData();

private slots:
    void on_sendMessage_bt_pressed();
    void messageDispatcher(const QString &msg);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_bt_connexion_clicked();
};

#endif // MAINWINDOW_H
