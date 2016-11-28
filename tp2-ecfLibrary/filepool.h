#ifndef FILEPOOL_H
#define FILEPOOL_H
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>

class FilePool : public QStringList
{
public:
    FilePool();
    FilePool(const QString &folder);
    FilePool(const QString &folder, const QString &suffix);
    void findFileInFolderAndSubfolders(const QString &folder);
    void findFileWithOutSuffix(const QString &folder);

    QString tryGetFile();
    int count();
private:
    QString m_folder;
    QString m_suffix;

    QMutex mutex_;
    QStringList m_List_files;

};

#endif // FILEPOOL_H
