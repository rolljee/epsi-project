#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "fileselector.h"


class QTextEdit;
class QLineEdit;
class QDir;
class QProgressBar;
class DirectorySelector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void compress();
    void decompress();
    void directoryChanged(const QDir &dir);


private:
    DirectorySelector *directorySelector_;
    FileSelector *fileSelector;
    QFileDialog *file_dialog;
    QLineEdit *ecf_file;

};

#endif // MAINWINDOW_H
