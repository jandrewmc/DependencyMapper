#include "graph.h"
#include "graphdata.h"
#include "graphviztools.h"
#include <string>
#include <unordered_map>
#include <QList>
#include <QString>
#include <QHash>
#include <QtDebug>

void Graph::addEdge(Edge edge)
{
    _edges.insert(edge);
}

void Graph::addNode(QString name)
{
    _nodes.insert(name);
}

void Graph::processList(GraphDataList list)
{
    foreach (GraphData item, list)
    {
        QString name = item.name;
        addNode(item.name);

        foreach (RequiresPair requires_, item.requires_)
        {
            QPair<QString, QString> edge;

            edge.first = requires_.first;
            edge.second = name;

            addEdge(edge);
        }

        foreach (RequiredByPair requiredBy_, item.requiredBy_)
        {
            QPair<QString, QString> edge;

            edge.first = name;
            edge.second = requiredBy_.first;

            addEdge(edge);
        }
    }

}

QString Graph::generateDotFile()
{
    GraphvizTools x;
    QString dotFilePath(x.dataToDot(_edges));
    //qDebug().nospace() << "TEST:" + dotFilePath;
    return dotFilePath;

}

void Graph::generateImage(QString filepath)
{
    GraphvizTools x;
    x.generateGraphviz(filepath);
}

