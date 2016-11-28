#ifndef FINDINFILE_H
#define FINDINFILE_H
#include <QFile>
#include <QTextStream>

class FindInFile
{
public:
    FindInFile();
    FindInFile(const QString &_searched_text);
    bool operator() (const QString &filename) const;
private:
    const QString searched_text;
};

#endif // FINDINFILE_H

