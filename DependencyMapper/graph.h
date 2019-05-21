#ifndef GRAPH_H
#define GRAPH_H
#include <QPair>
#include <QString>
#include <QList>
#include "graphdata.h"
#include <QHash>
#include <QSet>

typedef QPair<QString, QString> Edge;


class Graph
{
public:
    void addEdge(Edge edge);
    void addNode(QString name);
    void processList(GraphDataList list);
    QString generateDotFile();
    void generateImage(QString filepath);
private:
    QSet<QString> _nodes;
    QSet<Edge> _edges;
};

#endif // GRAPH_H\
