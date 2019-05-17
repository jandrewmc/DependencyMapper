#ifndef PARSECONANDATA_H
#define PARSECONANDATA_H

#include <QString>
#include <QStringList>
#include "graphdata.h"

namespace dependencymapper
{
class ParseConanData
{
public:
    GraphDataList parseConanData(QString data);

private:
    GraphData processDataBlock(QStringList dataBlock);

private:
    void processNodeNameVersion(QString data, GraphData& graphData);
    void processRequires(QString data, GraphData& graphData);
    void processRequiredBy(QString data, GraphData& graphData);

    void processConanName(QString item, QString& name, QString& version);
};
}
#endif // PARSECONANDATA_H
