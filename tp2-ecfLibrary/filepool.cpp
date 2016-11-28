#include "filepool.h"

FilePool::FilePool()
{
}

FilePool::FilePool(const QString &folder)
    : m_folder(folder)
{
     findFileWithOutSuffix(m_folder);
}
FilePool::FilePool(const QString &folder, const QString &suffix)
    : m_folder(folder),
      m_suffix(suffix)
{
    findFileInFolderAndSubfolders(m_folder);
}
void FilePool::findFileInFolderAndSubfolders(const QString &folder)
{
    QDir dir(folder);
    foreach (const QFileInfo &entry,
             dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
        if( entry.isDir() == true )
        {
            findFileInFolderAndSubfolders(entry.filePath());
        }
        else if(entry.isFile() == true
                && entry.suffix() == m_suffix) {
            m_List_files.append(entry.absoluteFilePath());
        }
    }
}
void FilePool::findFileWithOutSuffix(const QString &folder)
{
    QDir dir(folder);
    foreach (const QFileInfo &entry,
             dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
        if( entry.isDir() == true ){

            findFileInFolderAndSubfolders(entry.filePath());
        }
        else if(entry.isFile() == true) {

            m_List_files.append(entry.absoluteFilePath());
        }
    }
}
int FilePool::count() {
    QMutexLocker locker(&mutex_);
    return m_List_files.size();
}
QString FilePool::tryGetFile() {
    QString file;
    // Début de d'exclusion mutuelle
    QMutexLocker locker(&mutex_);
    // Aucun autre thread ne peut exécuter ce code
    // pour le moment
    if(m_List_files.isEmpty() == false) {
        file = m_List_files.front();
        m_List_files.pop_front();
    }
    return file;
    // A la destruction de locker, les autres
    // threads pourront à nouveau essayer d'exécuter
    // ce code.
}
