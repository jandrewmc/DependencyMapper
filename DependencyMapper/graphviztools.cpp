#include "graphviztools.h"
#include "graph.h"
#include "graphdata.h"
#include <QString>

void graphVIzTools::gVIzTools()
{
    QString dotCode = "digraph G {\n";

    foreach (Edge e, _edges)
    {
        dotCode = dotCode + e.first + " -> " + e.second;
    }
    dotCode = dotCode + "}";

}
