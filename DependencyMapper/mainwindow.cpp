#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include <QFileDialog>
#include <readfile.h>
#include "graphdata.h"
#include <QString>
#include "parseconandata.h"
#include "graphviztools.h"
#include <QtDebug>
#include "graphtools.h"
#include <QCheckBox>
#include <QMap>

namespace  {
bool stringLessThan(const QString &v1, const QString &v2)
{
     return v1 < v2;
}

QString listKey(QList<QString> list)
{
    std::sort(list.begin(), list.end(), stringLessThan);
    QString result;
    result.append("[");
    foreach (QString item, list)
        result.append(item + ", ");
    QString ret = result.mid(0, result.size()-1);
    ret += "] is a cycle";
    return ret;
}
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->generateBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateBtn_clicked()
{
    // File will be read
    // raw data will be parsed into GraphData

    readFile f;
    QString rawData = f.readFileName(ui->pathLbl->text());

    dependencymapper::ParseConanData pcd;
    GraphDataList list = pcd.parseConanData(rawData);

    // start from here
    Graph g;
    GraphTools gt;
    bool showFileDependencies;
    bool showRedundanciesAndCycles;


    showFileDependencies = ui->fileCheckBox->isChecked();
    showRedundanciesAndCycles = ui->showRedundanciesAndCycles_Btn->isChecked();

    g.processList(list);
    gt.setGraph(g);
    QString pathFILE = gt.generateDotFile(showFileDependencies);

    QSet<Edge> _edgesS;
    if (showFileDependencies)
        _edgesS = g.getEdgesFilename();
    else
        _edgesS = g.getEdgesNoFilename();

    bool red = false;

    if (showRedundanciesAndCycles)
    {
        foreach (Edge e, _edgesS)
        {
            red = gt.detectRedundanciesHelper(e.first, e.second, _edgesS);
            if (red)
                qDebug() << e.first + ", " + e.second + " is redundant";

        }
     }

    //bool cycl = false;
    /*
    foreach (Edge e, _edgesS)
    {
        cycl = gt.detectCycles(e.first,prev, _edgesS);
        if (cycl)
        {
            cycle.insert(e.first);
        }
    }
    QString fullCycle;
    foreach (QString n, cycle)
    {
        fullCycle += n + ", ";
    }
    qDebug().nospace() << fullCycle + " are in a cyclical redundancy";
    */

    if (showRedundanciesAndCycles)
    {
        QList<QString> prev;
        QSet<QString> cycle;
        QList<QString> individualCycle;
        QSet<QString> allCycles;

        QHash<QString, QList<QString> > allCycles2;



        foreach (Edge e, _edgesS)
        {
            individualCycle = gt.detectCycles(e.first,prev, _edgesS);
            if (individualCycle.size() != 0)
            {
                //qDebug() << individualCycle;
                //qDebug() << "is cyclical\n";
//                QMap<QString, int> map;

                allCycles.insert(listKey(individualCycle));

//                qSort(individualCycle.begin(), individualCycle.end(), stringLessThan);

                //converting lists to maps to esnure they are ordered
//                foreach (QString s, individualCycle)
//                    map.insert(s, 0);
//                allCycles.insert(map);
            }
        }

        foreach (QString item, allCycles)
        {
            qDebug() << item;
        }



        //qDebug << allCycles;
        /*
        for (int i = 0; i < allCycles.count(); i++)
        {
            QList<QString> mapv2 = allCycles.val


        }
        */
        /*
        foreach (QMap<QString,int> m, listedSet)
        {

            //foreach(QString s, m)
              //  test += s + ", ";
        }


        test += "]";
        qDebug() << test;
        */
     }

    //This method should run a command line function to generate a PNG image using the data.dot file we created.
    //This should function properly with a rewrite on a non-MacOS system.
    gt.generateGraph(pathFILE);

}

void MainWindow::on_browseBtn_clicked()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Find file to parse");
    if(dialog.exec())
    {
        ui->pathLbl->setText(dialog.selectedFiles().first());
    }
    ui->generateBtn->setEnabled(!ui->pathLbl->text().isEmpty());
}


