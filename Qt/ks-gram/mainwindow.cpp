#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ruleCount = 0;
    G = new StringsGenerator;
    isCreate=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    if(isCreate)on_pushButton_3_clicked();
    ruleCount=NoTerm.size();
    for(int i=0;i<ruleCount;i++)
    {
        QHBoxLayout *Hlay = new QHBoxLayout;
        lineEditArray[i] = new QLineEdit(this);
        labelRule[i] = new QLabel(this);
        point[i] = new QLabel(this);
        labelRule[i]->setText(NoTerm.at(i));
        point[i]->setText("->");
        Hlay->addWidget(labelRule[i]);
        Hlay->addWidget(point[i]);
        Hlay->addWidget(lineEditArray[i]);
        ui->verticalLayout->addLayout(Hlay);

    }
    isCreate=true;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str;
    QStringList r,NoTermsEmpty;
    Term.clear();
    Rules.clear();
    NoTermsEmpty.clear();
    str = ui->lineEdit_Term->text();
    Term = str.split(",");

    for(int i=0;i<ruleCount;i++)
    {
        str = lineEditArray[i]->text();
        r=str.split("|");
        Rules[labelRule[i]->text()]=r;
        if(r.contains("$"))
        {
            NoTermsEmpty.append(labelRule[i]->text());
        }
        r.clear();
    }

   fromN=ui->spinBox_from->value();
   toN=ui->spinBox_to->value();
   qDebug()<<fromN<<toN;
   G->SetParemeters(Term,NoTerm,Rules,StartTerm,fromN,toN);
   G->Start(NoTermsEmpty);
   PrintResult(G->Print());
}

void MainWindow::on_lineEdit_StartTerm_editingFinished()
{
    StartTerm=ui->lineEdit_StartTerm->text();
}

void MainWindow::on_lineEdit_NoTerm_editingFinished()
{

    QString str;
    str = ui->lineEdit_NoTerm->text();
    NoTerm = str.split(",");
}
void MainWindow::PrintResult(QStringList List)
{
    ui->textEdit_res->clear();
    qSort(List.begin(), List.end(), MyLessThan);
    for(int i = 0; i<List.size();i++)
    {
        ui->textEdit_res->append(List.at(i));
    }
}
bool MainWindow::MyLessThan(const QString &s1, const QString &s2)
{
  return (s1.size() < s2.size());
}

void MainWindow::on_pushButton_3_clicked()
{
    for(int i=0;i<ruleCount;i++)
    {
        lineEditArray[i]->close();
        labelRule[i]->close();
        point[i]->close();
    }
    ruleCount=0;
    isCreate=false;
    Term.clear();
    Rules.clear();
    ui->lineEdit_NoTerm->clear();
    ui->lineEdit_StartTerm->clear();
    ui->lineEdit_Term->clear();
}
