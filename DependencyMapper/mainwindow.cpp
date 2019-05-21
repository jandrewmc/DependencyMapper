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
    QString pathFILE = g.generateDotFile();
    //qDebug().nospace() << "TEST 2:" + pathFILE;
    g.generateImage(pathFILE);

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
