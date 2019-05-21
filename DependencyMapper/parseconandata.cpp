#include "parseconandata.h"

#include <QStringList>
#include "graphdata.h"

GraphDataList dependencymapper::ParseConanData::parseConanData(QString data)
{
    GraphDataList graphDataList;

    QStringList dataLines = data.split("\n");

    QStringList dataBlock;
    foreach (QString dataLine, dataLines)
    {
        if (!dataLine.isEmpty())
        {
            if (!dataLine.at(0).isSpace())
            {
                GraphData d = processDataBlock(dataBlock);
                if (!d.name.isEmpty())
                {
                    graphDataList.append(d);
                }
                dataBlock.clear();
            }
            dataBlock.append(dataLine);
        }
    }
    graphDataList.append(processDataBlock(dataBlock));
    return graphDataList;
}

GraphData dependencymapper::ParseConanData::processDataBlock(QStringList dataBlock)
{
    GraphData graphData;

    QString data = dataBlock.join("\n");

    processNodeNameVersion(data, graphData);

    processRequires(data, graphData);

    processRequiredBy(data, graphData);

    return graphData;
}

void dependencymapper::ParseConanData::processNodeNameVersion(QString data, GraphData &graphData)
{
    QStringList items = data.split("\n");
    foreach (QString item, items)
    {
        if (!item.isEmpty())
        {
            if (!item.at(0).isSpace())
            {
                processConanName(item, graphData.name, graphData.version);
            }
        }
    }
}

void dependencymapper::ParseConanData::processRequires(QString data, GraphData &graphData)
{
    QStringList requiresItems;
    QStringList items = data.split("\n");
    for (int index = 0; index < items.count(); index++)
    {
        QString item = items.at(index);

        if (item.contains("Requires", Qt::CaseInsensitive))
        {
            int lookAheadIndex = index + 1;
            while (lookAheadIndex < items.count() && !items.at(lookAheadIndex).contains("Required By", Qt::CaseInsensitive))
            {
                requiresItems << items.at(lookAheadIndex).trimmed();
                lookAheadIndex++;
            }
        }
    }

    foreach (QString item, requiresItems)
    {
        RequiresPair rp;
        processConanName(item, rp.first, rp.second);
        graphData.requires_.append(rp);
    }
}

void dependencymapper::ParseConanData::processRequiredBy(QString data, GraphData &graphData)
{
    QStringList requiredByItems;
    QStringList items = data.split("\n");
    for (int index = 0; index < items.count(); index++)
    {
        QString item = items.at(index);

        if (item.contains("Required By", Qt::CaseInsensitive))
        {
            int lookAheadIndex = index + 1;
            while (lookAheadIndex < items.count() && !items.at(lookAheadIndex).contains("Requires", Qt::CaseInsensitive))
            {
                requiredByItems << items.at(lookAheadIndex).trimmed();
                lookAheadIndex++;
            }
        }
    }

    foreach (QString item, requiredByItems)
    {
        RequiredByPair rbp;
        processConanName(item, rbp.first, rbp.second);
        graphData.requiredBy_.append(rbp);
    }
}

void dependencymapper::ParseConanData::processConanName(QString item, QString &name, QString &version)
{
    QStringList firstSplit = item.split("@");
    if (firstSplit.count() == 2)
    {
        QString firstHalf = firstSplit.first();
        QStringList secondSplit = firstHalf.split("/");
        if (secondSplit.count() == 2)
        {
            name = secondSplit.first().trimmed();
            version = secondSplit.last().trimmed();
        }
        else
        {
            // Not sure what to do here
        }
    }
    else
    {
        name = item.trimmed();
    }
}
