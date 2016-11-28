#include "findinfile.h"

FindInFile::FindInFile()
{
}
FindInFile::FindInFile(const QString &_searched_text):
    searched_text(_searched_text)
{

}

bool FindInFile::operator()(const QString &filename) const {
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }

    QTextStream stream (&file);
    while(!stream.atEnd()){
        if (stream.readLine().contains(searched_text)) {
            return true;
        }
    }
    return false;
}
