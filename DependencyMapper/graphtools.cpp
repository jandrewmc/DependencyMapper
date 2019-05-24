#include "graphtools.h"
#include <QDebug>

QString GraphTools::generateDotFile(bool showFileDependencies)
{
    GraphvizTools x;
    QString dotFilePath;

    if (showFileDependencies)
    {
        QSet<Edge> _edgesS = _graph.getEdgesFilename();
        dotFilePath = x.dataToDot(_graph.getEdgesFilename());
    }
    else
        dotFilePath = x.dataToDot(_graph.getEdgesNoFilename());
    return dotFilePath;
}

void GraphTools::setGraph(Graph graph)
{
    _graph = graph;
}

void GraphTools::generateGraph(QString filepath)
{
    GraphvizTools x;
    x.generateGraphviz(filepath);
}

//Detects redundancy for one edge
bool GraphTools::detectRedundanciesHelper(QString n1, QString n2, QSet<Edge> _edgesS)
{
    foreach (Edge e, _edgesS)
    {
        if (e.first == n1 && e.second != n2)
        {
            if (detectRedundancies(e.second, n2, n1, _edgesS))
            {
                return true;
            }
        }
    }
    return false;
}
bool GraphTools::detectRedundancies(QString n1, QString n2, QString start, QSet<Edge> _edgesS)
{
    //Base Cases
    if (n1 == n2) return true;
    if (n1 == start) return false;

    foreach (Edge e, _edgesS)
    {
        if (e.first == n1)
        {
            if (detectRedundancies(e.second, n2, start, _edgesS))
            {
                return true;
            }
        }
    }
    return false;
}

QList<QString> GraphTools::detectCycles(QString node, QList<QString> list, QSet<Edge> _edgesS)
{
    foreach(QString n, list)
    {
        if (node == n) return list;
    }
    foreach (Edge e, _edgesS)
    {
        if (e.first == node)
        {
            list.append(node);
            //if (detectCycles(e.second,list, _edgesS)) return list;
            //return
            QList<QString> listy = detectCycles(e.second,list, _edgesS);
            if (listy.size() != 0) return listy;
            list.removeLast();
        }
    }
    list.clear();
    return list;
}



