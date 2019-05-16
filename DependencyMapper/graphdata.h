#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QPair>
#include <QString>

typedef QString Name;
typedef QString Version;

typedef QPair<Name, Version> RequiresPair;
typedef QPair<Name, Version> RequiredByPair;

typedef QList<RequiresPair> Requires;
typedef QList<RequiredByPair> RequiredBy;

struct GraphData {
    Name name;
    Version version;
    Requires requires;
    RequiredBy requiredBy;
};

typedef QList<GraphData> GraphDataList;

#endif // GRAPHITEM_H
