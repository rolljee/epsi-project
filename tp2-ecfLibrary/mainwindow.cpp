#include "mainwindow.h"
#include "directoryselector.h"
#include "findinfile.h"
#include "epsifilecompressor.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include "filepool.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto window = new QWidget(this);

    directorySelector_ = new DirectorySelector(window);
    fileSelector = new FileSelector(window);

    ecf_file = new QLineEdit("/home/epsi/tp2-test-decompress/Output.ecf", window);
    auto button_compress = new QPushButton("Compress",window);
    auto button_decompress = new QPushButton("Decompress",window);
    auto layout = new QVBoxLayout;

    layout->addWidget(new QLabel("Compress the choosen folder:", window));
    layout->addWidget(directorySelector_);
    layout->addWidget(new QLabel("Output :", window));


    layout->addWidget( ecf_file );

    layout->addWidget(button_compress);
    layout->addWidget(fileSelector);
    layout->addWidget(button_decompress);

    connect(button_compress,SIGNAL(clicked()),this,SLOT(compress()));
    connect(button_decompress,SIGNAL(clicked()),this,SLOT(decompress()));
    connect(directorySelector_,SIGNAL(directoryChanged(QDir)),this,SLOT(directoryChanged(QDir)));

    window->setLayout(layout);
    setCentralWidget(window);
    show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::compress()
{
    EpsiFileCompressor compressor(2);
    QString folder(directorySelector_->currentFolder().absolutePath());
    QString dest_fileName(ecf_file->text());
    compressor.compress(folder,dest_fileName);
}

void MainWindow::decompress(){
    EpsiFileCompressor compressor(2);
    QString file(fileSelector->getFileName());
    QString dest_fileName(fileSelector->getActualDirectory());
    compressor.uncompress(file,dest_fileName);
}

void MainWindow::directoryChanged(const QDir &/*dir*/) {

}

