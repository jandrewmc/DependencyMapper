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

