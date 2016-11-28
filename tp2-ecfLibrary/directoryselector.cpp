#include "directoryselector.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

DirectorySelector::DirectorySelector(QWidget *parent) :
    QWidget(parent),currentFolder_("c:\\")
{
    auto button = new QPushButton("...", this);
    folder_ = new QLineEdit(currentFolder().absolutePath(), this);
    auto layout = new QHBoxLayout;
    layout->addWidget(folder_);
    layout->addWidget(button);

    connect(button, SIGNAL(clicked()),this, SLOT(selectFolder()));
    connect(folder_,SIGNAL(editingFinished()),this, SLOT(validateFolder()));

    setLayout(layout);
}
void DirectorySelector::selectFolder() {

    QFileDialog dialog;

    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(currentFolder());
    if( dialog.exec() == QFileDialog::Accepted ) {
        folder_->setText(dialog.directory().absolutePath());
        currentFolder_ = dialog.directory();
        emit directoryChanged( currentFolder_ );
    }

}
void DirectorySelector::validateFolder() {
    QDir newDir( folder_->text());
    if( newDir.exists() == false) {
        QMessageBox::critical(this, "Invalid folder",QString("%1 is not a valid folder").arg(folder_->text()),QMessageBox::Ok);
        folder_->setText(currentFolder_.absolutePath());
    }
    else {
        currentFolder_ = newDir;
        emit directoryChanged( currentFolder_ );
    }
}
const QDir &DirectorySelector::currentFolder()const {
    return currentFolder_;
}
