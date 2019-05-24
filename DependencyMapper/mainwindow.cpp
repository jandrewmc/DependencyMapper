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

    //QSet<Edge> _edgesS = _graph.getEdgesFilename();
    bool red = false;
    foreach (Edge e, g.getEdgesFilename())
    {
        red = gt.detectRedundanciesHelper(e.first, e.second);
        if (red)
            qDebug() << e.first + ", " + e.second + " is redundant";

    }

    bool cycl = false;
    QList<QString> prev;
    foreach (Edge e, g.getEdgesFilename())
    {
        cycl = gt.detectCycles(e.first,prev);
        if (cycl)
            qDebug() << e.first + " is cyclical";
    }
    //

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


