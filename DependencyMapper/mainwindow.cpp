#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

#include "graphdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateBtn_clicked()
{
    // File will be read
    // raw data will be parsed into GraphData

    GraphDataList list;

    // start from here

    Graph g;
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


