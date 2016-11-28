#ifndef DIRECTORYSELECTOR_H
#define DIRECTORYSELECTOR_H

#include <QWidget>
#include <QDir>
class QLineEdit;
class DirectorySelector : public QWidget
{
    Q_OBJECT
public:
    explicit DirectorySelector(QWidget *parent = 0);
    const QDir &currentFolder()const;
signals:
    void directoryChanged( const QDir &directory );
public slots:
    void validateFolder();


private slots:
    void selectFolder();

private:
    QLineEdit *folder_;
    QDir currentFolder_;
};

#endif // DIRECTORYSELECTOR_H
