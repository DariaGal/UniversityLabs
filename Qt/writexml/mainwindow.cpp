#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "saxparser.h"
#include "writexml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->clear();
    SaxParser parser(ui->treeWidget);
    parser.readFile("C:\\qt project\\2.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    WriteXml xmlToFile(ui->treeWidget);
    xmlToFile.writeXml("C:\\qt project\\3.xml");
}
