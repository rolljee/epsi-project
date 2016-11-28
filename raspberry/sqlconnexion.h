#ifndef SQLCONNEXION_H
#define SQLCONNEXION_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

class Sqlconnexion
{
public:
    Sqlconnexion();
    QString bddPicture(QString code);

private:
    QSqlDatabase db;
};
#endif // SQLCONNEXION_H
