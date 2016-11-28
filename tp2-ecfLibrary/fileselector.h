#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>
#include <QFile>


class QLineEdit;
class FileSelector : public QWidget
{
    Q_OBJECT
public:
    explicit FileSelector(QWidget *parent = 0);
    QString getActualDirectory() const;
    QString getFileName() const;
signals:
    void filepathChanged( const QFile &fileName );
public slots:

private slots:
    void selectFile();

private:
    QLineEdit *fileName;
    QFile currentFile;
    QString actualDirectory;
};

#endif // FILESELECTOR_H
