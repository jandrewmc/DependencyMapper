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
    //Redundant test
    QPair<QString, QString> edge;
    edge.first = "CCCC";
    edge.second = "UUUU";
    addEdge(edge);

    //Cycle test
    edge.first = "CCCC";
    edge.second = "cycle1";
    addEdge(edge);
    edge.first = "cycle1";
    edge.second = "cycle2";
    addEdge(edge);
    edge.first = "cycle2";
    edge.second = "CCCC";
    addEdge(edge);
}

QSet<Edge> Graph::getEdgesFilename()
{
    return _edges;
}

QSet<Edge> Graph::getEdgesNoFilename()
{
    QSet<Edge> ret = _edges;
    foreach (Edge e, ret)
    {
        if (e.second == "conanfile.txt")
            ret.remove(e);
    }

    return ret;
}

