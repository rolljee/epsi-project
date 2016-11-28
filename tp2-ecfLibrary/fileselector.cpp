#include "fileselector.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

FileSelector::FileSelector(QWidget *parent) :
    QWidget(parent),
    currentFile("/home/epsi/Output.ecf")
{
    auto button = new QPushButton("...", this);
    fileName = new QLineEdit(currentFile.fileName(),this);
    auto layout = new QHBoxLayout;
    layout->addWidget(fileName);
    layout->addWidget(button);
    connect(button,SIGNAL(clicked()),this,SLOT(selectFile()));

    setLayout(layout);
}

QString FileSelector::getActualDirectory() const
{
    return actualDirectory;
}

QString FileSelector::getFileName() const
{
    return fileName->text();
}

void FileSelector::selectFile()
{
    QFileDialog dialog;
    dialog.exec();
    actualDirectory = dialog.directory().absolutePath();
    fileName->setText(dialog.selectedFiles().first());
}




