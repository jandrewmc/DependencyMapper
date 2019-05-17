#ifndef READFILE_H
#define READFILE_H
#include <Qstring>

typedef QString FileData;

class readFile
{
public:
    QString readFileName(QString filename);
private:
    FileData data;
};

#endif // READFILE_H
