#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(MyTcpServer *server, Sqlconnexion *connector, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    m_serv(server),
    m_connector(connector)
{
    ui->setupUi(this);
    connect(m_serv,SIGNAL(code(QString)),this,SLOT(decode_code(QString)));
    connect(this,SIGNAL(getBddPicture(QString)),this,SLOT(decode_picture_bdd(QString)));
    connect(m_serv,SIGNAL(picture(QPixmap)),this,SLOT(decode_picture(QPixmap)));
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::decode_code(const QString code){
    QString strCode = "Code : "+code;
    if(code.isEmpty() == false){
        ui->code_label->setText(strCode);
        emit getBddPicture(code);
    } else {
        ui->code_label->clear();
        ui->raspberry_label->clear();
        ui->BDD_label->clear();
    }
}

void MainWindow::decode_picture(QPixmap picture){
    qDebug() << picture;
    if (picture.isNull() == false) {
        ui->raspberry_label->setPixmap(picture);
    } else {
        ui->code_label->clear();
        ui->raspberry_label->clear();
        ui->BDD_label->clear();
    }
}

void MainWindow::decode_picture_bdd(const QString code){
    QString qstring_photo;
    if(code.isEmpty() == false){
       qstring_photo  = m_connector->bddPicture(code);
    }
    if (qstring_photo.isEmpty() == false) {
        QPixmap pix(qstring_photo);
        QPixmap newPixmap = pix.scaled(QSize(300,300),  Qt::KeepAspectRatio);
        ui->BDD_label->setPixmap(newPixmap);
    } else {
        qDebug() << "Value is null, no picture found";
        ui->code_label->clear();
        ui->raspberry_label->clear();
        ui->BDD_label->clear();
        QMessageBox::critical(
                    this,
                    tr("Visual vision"),
                    tr("No picture found, code is wrong.") );
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->code_label->text().isEmpty()) {
        QString msg = "YES";
        m_serv->getSocket()->getSocket()->write(m_serv->getSocket()->packMessage(msg));
    } else {
        qDebug() << "No connexion, response aborted";
        QMessageBox::critical(
                    this,
                    tr("Visual vision"),
                    tr("No connexion, response aborted") );
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!ui->code_label->text().isEmpty()) {
        QString msg = "NO";
        m_serv->getSocket()->getSocket()->write(m_serv->getSocket()->packMessage(msg));
    } else {
        qDebug() << "No connexion, response aborted";
        QMessageBox::critical(
                    this,
                    tr("Visual vision"),
                    tr("No connexion, response aborted") );
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    switch( QMessageBox::question(
                this,
                tr("Application Name"),
                tr("Clean everything from UI ?"),

                QMessageBox::Yes |
                QMessageBox::No ) )
    {
    case QMessageBox::Yes:
        ui->raspberry_label->clear();
        ui->BDD_label->clear();
        break;
    case QMessageBox::No:
        qDebug( "no" );
        break;
    default:
        qDebug( "close" );
        break;
    }

}
