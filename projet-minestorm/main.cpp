#include "mainwindow.h"
#include "minestorm.h"
#include <QSize>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minestorm game(QSize(800,800));
    MainWindow w(&game);
    return a.exec();
}
