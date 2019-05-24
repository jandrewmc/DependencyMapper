#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#include <QString>
#include <graph.h>
#include <graphviztools.h>
#include <graphdata.h>


class GraphTools
{
public:
    void generateGraph(QString filepath);
    bool detectRedundanciesHelper(QString n1, QString n2,  QSet<Edge> edgs);
    bool detectRedundancies(QString n1, QString n2, QString start, QSet<Edge> edgs);
    QString generateDotFile(bool showFileDependencies);
    QList<QString> detectCycles(QString n, QList<QString> list, QSet<Edge> edgs);
    void setGraph(Graph graph);
private:
    Graph _graph;
};

#endif // GRAPHTOOLS_H
