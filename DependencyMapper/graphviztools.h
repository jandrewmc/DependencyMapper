#ifndef GRAPHVIZTOOLS_H
#define GRAPHVIZTOOLS_H
#include <QPair>
#include <QString>
#include <QList>
#include "graphdata.h"
#include <graph.h>
#include <QHash>
#include <QSet>

class GraphvizTools
{
public:
    QString dataToDot(QSet<Edge> edges);
    void generateGraphviz(QString filename);
};

#endif // GRAPHVIZTOOLS_H
