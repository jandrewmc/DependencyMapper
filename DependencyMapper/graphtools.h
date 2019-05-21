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
    void detectCycles();
};

#endif // GRAPHTOOLS_H
