#include "graphviztools.h"
#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>
#include <graph.h>
#include <QProcess>
#include<QtDebug>

QString GraphvizTools::dataToDot(QSet<Edge> edges)
{
    QFile file("/Users/colin_brosnan/nasadev/DependencyMapper/data.dot");

    if (file.exists())
        file.remove();

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write("digraph G {\n");
        file.write("subgraph clusterApple {\n");

        QString nLine = "node [style=filled fillcolor=\"#ffffff\"]\n";
        file.write(nLine.toLocal8Bit());

        nLine = "node [color=\"#ff0000\"]\n";
        file.write(nLine.toLocal8Bit());

        nLine = "bgcolor = \"#0000ff2f\"\n";
        file.write(nLine.toLocal8Bit());

        foreach(Edge e, edges)
        {
            if (e.second == "conanfile.txt")
            {
                QString line = e.first + " -> " + "\"conanfile.txt\"" + ";\n";
                file.write(line.toLocal8Bit());
            }

            else
            {
                QString line = e.first + " -> " + e.second + ";\n";
                file.write(line.toLocal8Bit());
            }
        }

        file.write("}\n");
        //
        QString newLine = "bgcolor=\"#0000000f\"\n";
        file.write(newLine.toLocal8Bit());

        newLine = "label = \"Dependency Mapper\nNASA\"\n";
        file.write(newLine.toLocal8Bit());

        newLine = "fontsize=20\n";
        file.write(newLine.toLocal8Bit());

        file.write("}");
    }

    file.close();

    //qDebug().nospace() << file.fileName();
    return file.fileName();
}

void GraphvizTools::generateGraphviz(QString filepath)
{
    QStringList args;
    args << "-Tpng"
         << filepath
         << ">"
         << "/Users/colin_brosnan/nasadev/DependencyMapper/output.png";
         //<< QString("%1 > %2").arg(filepath, "/Users/colin_brosnan/nasadev/DependencyMapper/output.png");

    QProcess p;
    p.start("/usr/local/bin/dot", args);
    bool s = p.waitForStarted();
    bool f = p.waitForFinished();
    QString stdout = p.readAllStandardOutput();
    QString stderr = p.readAllStandardError();
    qDebug() << stdout;
    qDebug() << stderr;
    bool res = false;
}


