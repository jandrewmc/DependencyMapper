#include "graph.h"
#include "graphdata.h"
#include <string>
#include <unordered_map>
#include <QList>
#include <QString>
#include <QHash>

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
    Graph g;
    foreach (GraphData item, list)
    {
        QString name = item.name;
        g.addNode(item.name);

        foreach (RequiresPair requires, item.requires)
        {
            QPair<QString, QString> edge;

            edge.first = requires.first;
            edge.second = name;

            g.addEdge(edge);
        }


        foreach (RequiredByPair requiredBy, item.requiredBy)
        {
            QPair<QString, QString> edge;

            edge.first = name;
            edge.second = requiredBy.first;

            g.addEdge(edge);
        }
    }
}
digraph G
{

}
