#include <iostream>
#include "readfile.h"
#include <QString>
#include <QFile>
#include <QtDebug>

QString readFile::readFileName(QString filename)
{
    QByteArray ret;
    QString dataAsString = "";
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       ret = f.readAll();
       dataAsString = QString(ret);
    }
    qDebug().nospace() << dataAsString;
    return dataAsString;
}

/*QString readFileName(QString filename)
{
    QString ret;
    QFile f(filename);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       ret = f.readAll();
    }

    cout << ret;
    return ret;
}*/
