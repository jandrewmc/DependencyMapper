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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pathLbl->setText("");
    ui->generateBtn->setEnabled(false);
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


    showFileDependencies = ui->fileCheckBox->isChecked();

    g.processList(list);
    gt.setGraph(g);
    QString pathFILE = gt.generateDotFile(showFileDependencies);

    QSet<Edge> _edgesS;
    if (showFileDependencies)
        _edgesS = g.getEdgesFilename();
    else
        _edgesS = g.getEdgesNoFilename();

    bool red = false;
    foreach (Edge e, _edgesS)
    {
        red = gt.detectRedundanciesHelper(e.first, e.second, _edgesS);
        if (red)
            qDebug() << e.first + ", " + e.second + " is redundant";

    }

    bool cycl = false;
    QList<QString> prev;
    QSet<QString> cycle;
    QList<QString> individualCycle;
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
    foreach (Edge e, _edgesS)
    {
        individualCycle = gt.detectCycles(e.first,prev, _edgesS);
            qDebug() << individualCycle;
        qDebug() << "is cyclical\n";
    }

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


