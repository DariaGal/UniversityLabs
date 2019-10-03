#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "checkstringdka.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir("C:/qt project/DKAtest");
    QStringList files = dir.entryList();
    files.removeAt(0);
    files.removeAt(0);
    ui->comboBox->addItems(files);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_createtable_clicked()
{
    //ui->tableWidget->clear();
    bool f=true;
    QString str = ui->lineEdit_states->text();
    States = str.split(",");
    States.removeDuplicates();
    str = ui->lineEdit_symbols->text();
    Symbols = str.split(",");
    Symbols.removeDuplicates();
    StartState = ui->lineEdit_startState->text();
    str = ui->lineEdit_finishStates->text();
    FinishStates = str.split(",");
    FinishStates.removeDuplicates();
    for(int i=0;i<FinishStates.size();i++)
    {
        if(!States.contains(FinishStates.at(i)))
            f=false;
    }
    if(States.contains(StartState)&&f)
    {
    ui->tableWidget->setRowCount(States.size());
    ui->tableWidget->setColumnCount(Symbols.size());
    for(int i=0;i<Symbols.size();i++)
    {
        ui->tableWidget->horizontalHeader()->resizeSection(i, 40);
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(Symbols.at(i)));
    }
    for(int i=0;i<States.size();i++)
    ui->tableWidget->setVerticalHeaderItem(i,new QTableWidgetItem(States.at(i)));
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    QString str= ui->tableWidget->item(row,column)->text();
    if(!States.contains(str)&&str!="-")
    {
        ui->tableWidget->item(row,column)->setText("");
    }
    ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);
}

void MainWindow::on_pushButton_check_clicked()
{
    QString strCheck=ui->lineEdit_checkString->text();
    /*QString **tableDKA = new QString *[States.size()+1];
    for (int i = 0; i < States.size()+1; i++)
        tableDKA[i] = new QString [Symbols.size()+1];
    for(int j=1;j<Symbols.size()+1;j++)
    {
        tableDKA[0][j]=Symbols.at(j-1);
    }
    for(int i=1;i<States.size()+1;i++)
    {
        tableDKA[i][0]=States.at(i-1);
        for(int j=1;j<Symbols.size()+1;j++)
            tableDKA[i][j]=ui->tableWidget->item(i-1,j-1)->text();
    }*/

    QMap <QString,QStringList> tableDKA;
    for (int i = 0; i < States.size(); i++)
    {
        QStringList strL;
         for(int j=0;j<Symbols.size();j++)
         {
             strL.append(ui->tableWidget->item(i,j)->text());
         }
        tableDKA[States.at(i)]=strL;
        strL.clear();
     }
    CheckStringDKA *DKA = new CheckStringDKA();
    DKA->SetParameters(tableDKA,States,Symbols,StartState,FinishStates,strCheck);
    PrintResult(DKA->Start());
}
void MainWindow::PrintResult(QStringList List)
{
    ui->textEdit->clear();
    for(int i = 0; i<List.size();i++)
    {
        ui->textEdit->append(List.at(i));
    }
}

void MainWindow::on_pushButton_fromFile_clicked()
{
    ui->tableWidget->clear();
    QFile file("C:/qt project/DKAtest/"+ui->comboBox->currentText());
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QString str = file.readLine();
        str.remove("\n");
        ui->lineEdit_symbols->setText(str);
        Symbols = str.split(",", QString::SkipEmptyParts);

        str = file.readLine();
        str.remove("\n");
        ui->lineEdit_states->setText(str);
        States = str.split(",", QString::SkipEmptyParts);

        str = file.readLine();
        str.remove("\n");
        StartState = str;
        ui->lineEdit_startState->setText(str);

        str = file.readLine();
        str.remove("\n");
        ui->lineEdit_finishStates->setText(str);
        FinishStates = str.split(",", QString::SkipEmptyParts);

        ui->tableWidget->setRowCount(States.size());
        ui->tableWidget->setColumnCount(Symbols.size());

        for(int i=0;i<Symbols.size();i++)
        {
            ui->tableWidget->horizontalHeader()->resizeSection(i, 40);
            ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(Symbols.at(i)));
        }
        for(int i=0;i<States.size();i++)
        ui->tableWidget->setVerticalHeaderItem(i,new QTableWidgetItem(States.at(i)));
        int r=0;

        while(!file.atEnd())
        {
             str = file.readLine();
             str.remove("\n");
             QStringList list = str.split(",", QString::SkipEmptyParts);qDebug()<<list;
             for(int i=0;i<Symbols.size();i++)
             {
                QTableWidgetItem *cell = new QTableWidgetItem;
                cell->setText(list.at(i)) ;
                 ui->tableWidget->setItem(r,i,cell);
             }
             r++;
        }
    }

}

void MainWindow::on_pushButton_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                    tr("Сохранить файл"),
                                    "C:/qt project/DKAtest/",
                                    "Text (*.txt);");
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream out( &file );
        for(int i=0;i<Symbols.size();i++)
         out <<Symbols.at(i)<<",";
        out <<endl;
        for(int i=0;i<States.size();i++)
         out <<States.at(i)<<",";
        out <<endl;
        out <<StartState<<"\n";
        for(int i=0;i<FinishStates.size();i++)
         out <<FinishStates.at(i)<<",";
        out <<endl;
        for(int i=0;i<States.size();i++)
        {
            for(int j=0;j<Symbols.size();j++)
            {
                QString str = ui->tableWidget->item(i,j)->text();
                if(str=="")
                {
                    out <<"-,";
                }
                else out <<str<<",";
            }
        out <<endl;
        }

        QDir dir("C:/qt project/DKAtest");
        QStringList files = dir.entryList();
        files.removeAt(0);
        files.removeAt(0);
        ui->comboBox->clear();
        ui->comboBox->addItems(files);
    }
}
