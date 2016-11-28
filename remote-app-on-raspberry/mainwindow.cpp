#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),_msgSize(0)
{
    ui->setupUi(this);
    _bytes = 0;
    QPixmap pix("assets/raspberry-pi-logo.png");
    QPixmap newPixmap = pix.scaled(QSize(300,300),  Qt::KeepAspectRatio);
    ui->photo_label->setPixmap(newPixmap);
    QPixmap logo("assets/logo-visual-domotique.PNG");
    QPixmap scaled_logo = logo.scaled(QSize(150,150),  Qt::KeepAspectRatio);
    ui->logo->setPixmap(scaled_logo);
    launchConnexion();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::connected()
{
    qDebug() << "Connection.";
}

void MainWindow::disconnected()
{
    qDebug() << "disconnected...";
    QMessageBox::critical(
         this,
         tr("Visual vision"),
         tr("A problem occured, connexion as been lost") );
}

void MainWindow::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
    _bytes += bytes;
}

void MainWindow::readyRead()
{
    qDebug() << "reading...";
    qDebug() << socket->readAll();
}

void MainWindow::on_sendMessage_bt_pressed(){
    QString msg = ui->lineEdit->text();
    if (onErrorState == false) {
        socket->write(packMessage(msg));
        socket->waitForBytesWritten();
        socket->flush();
        socket->write(packMessage(pic->getEncodedPictureInString()));
        qDebug() << socket->bytesToWrite();
        socket->waitForBytesWritten();
        qDebug() << "Message should have been sent now.";
    } else {
        QMessageBox::critical(
             this,
             tr("Visual vision"),
             tr("A problem occured, connexion has been lost...") );
    }

}

void MainWindow::launchConnexion(){
    socket = new QTcpSocket(this);
    connect(this,SIGNAL(receiveMessage(QString)),this,SLOT(messageDispatcher(QString)));
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readData()));
    qDebug() << "connecting...";
    socket->connectToHost("192.168.1.13",9999); //QHostAddress::LocalHost
    if(!socket->waitForConnected(5000)){
        qDebug() << "Error: " << socket->errorString();
        onErrorState = true;
        ui->label->setText("Disconnected");
    } else{ onErrorState = false; ui->label->setText("Connected"); }
}
void MainWindow::messageDispatcher(const QString &msg){
    qDebug() << "ClientApp dispatcher" << msg;
}

QByteArray MainWindow::packMessage(const QString &msg) const {
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16) 0;
    out << msg;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    return  block;
}

void MainWindow::readData(){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);
    if (_msgSize == 0){
        in >> _msgSize;
    }
    QString message;
    in >> message;
    _msgSize = 0;
    emit receiveMessage(message);
}

void MainWindow::on_pushButton_clicked(){
    pic->takePicture();
    QPixmap picture("/home/pi/app-picture.jpg");
    if(!picture.isNull()){
        QPixmap scaled_pic = picture.scaled(QSize(150,150),  Qt::KeepAspectRatio);
        ui->photo_label->setPixmap(scaled_pic);
    } else {
        QMessageBox::critical(
             this,
             tr("Visual vision"),
             tr("Picture not found, please try again or contact the administrator if the problem persist..") );
    }
}

void MainWindow::on_pushButton_2_clicked(){
    // OPEN PYTHON SCRIPT;
}

void MainWindow::on_bt_connexion_clicked()
{
    launchConnexion();
    if (onErrorState == true) {
        QMessageBox::critical(
             this,
             tr("Visual vision"),
             tr("Failed to connect to host, please contact the administrator") );
    } else {
        QMessageBox::information(
             this,
             tr("Visual vision"),
             tr("Succesfully connected to host.") );
    }
}
