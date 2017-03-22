#include "sqlconnexion.h"

Sqlconnexion::Sqlconnexion()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("raspberry");
    db.setUserName("root");
    db.setPassword("root");
    db.open() ? qDebug() << "mysql return ok" : qDebug() << "mysql return ko";
}

QString Sqlconnexion::setData(QString code)
{
    QString photo;
//    qDebug() << "MYSQL::code = " << code;
//    qDebug() << code.isEmpty();
//    if (code.isEmpty() == false) {
//        QSqlQuery qry;

//        qry.prepare( "SELECT photo FROM user WHERE code=:code" );
//        qry.bindValue(":code",code);
//        qry.exec();
//        while (qry.next()) {
//            photo = qry.value(0).toString();
//        }
//    } else {
//        photo = "";
//    }
//    qDebug() << photo;
    return photo;
}


