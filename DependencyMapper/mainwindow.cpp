#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include <QFileDialog>
#include <readfile.h>
#include "graphdata.h"
#include <QString>
#include <parseconandata.h>

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
    g.processList(list);
    foreach (GraphData item, list)
    {
        QString name = item.name;
        g.addNode(item.name);

        foreach (RequiresPair requires, item.requires)
        {
            QPair<QString, QString> edge;

            edge.first = requires.first;
            edge.second = name;

            g.addEdge(edge);
        }


        foreach (RequiredByPair requiredBy, item.requiredBy)
        {
            QPair<QString, QString> edge;

            edge.first = name;
            edge.second = requiredBy.first;

            g.addEdge(edge);
        }
    }
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
