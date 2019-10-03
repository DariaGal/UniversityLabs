#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "checkstringdmpa.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("q"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("a"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("w"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(""));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("q'"));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("w'"));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("a'"));
    for(int i=0;i<7;i++)
    {
        ui->tableWidget->horizontalHeader()->resizeSection(i, 45);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_addrow_clicked()
{
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    QString str = ui->lineEdit_states->text();
    States = str.split(",");
    States.removeDuplicates();
    str = ui->lineEdit_symbols->text();
    Symbols = str.split(",");
    str = ui->lineEdit_stack->text();
    StackSymbols = str.split(",");
    Symbols.removeDuplicates();
    StackSymbols.removeDuplicates();
}

void MainWindow::on_pushButton_deleterow_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void MainWindow::on_pushButton_check_clicked()
{
   bool err = false;
   QStringList msg;
   QString str = ui->lineEdit_finishStates->text();
   QStringList finish = str.split(",");
   rules.clear();

   for(int i=0;i<ui->tableWidget->rowCount();i++)
   {
       if(ui->tableWidget->item(i,0)->text()== ui->tableWidget->item(i,4)->text()&&ui->tableWidget->item(i,2)->text()==ui->tableWidget->item(i,5)->text()&&ui->tableWidget->item(i,1)->text()=="-")
     {
           msg.append("правило №"+QString::number(i+1)+" задано неверно");
           err = true;
           break;
     }
      QStringList r;
      QString l = ui->tableWidget->item(i,0)->text()+" "+ui->tableWidget->item(i,1)->text()+" "+ui->tableWidget->item(i,2)->text();
       r.append(ui->tableWidget->item(i,4)->text());
       r.append(ui->tableWidget->item(i,5)->text());
       r.append(ui->tableWidget->item(i,6)->text());
       rules[l]=r;
   }
   if(!err)
   {
    CheckStringDMPA DMPA(rules, ui->lineEdit_checkString->text(),ui->lineEdit_startState->text(),finish,Symbols,stackstart);
    PrintResult(DMPA.Start());
   }
   else
   {
       PrintResult(msg);
   }
}
void MainWindow::PrintResult(QStringList List)
{
    ui->textEdit->clear();
    for(int i = 0; i<List.size();i++)
    {
        ui->textEdit->append(List.at(i));
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if(column==0 || column ==4)
    {
        QString str= ui->tableWidget->item(row,column)->text();
        if(!States.contains(str))
        {
             ui->tableWidget->item(row,column)->setText("");
        }
    }
    if(column==1)
    {
        QString str= ui->tableWidget->item(row,column)->text();
        if(!Symbols.contains(str)&&str!="-")
        {
             ui->tableWidget->item(row,column)->setText("");
        }
    }
    if(column==2)
    {
        QString str= ui->tableWidget->item(row,column)->text();
        if(!StackSymbols.contains(str)&&str!="-")
        {
             ui->tableWidget->item(row,column)->setText("");
        }
    }
     if(column==5)
     {
         QString str= ui->tableWidget->item(row,column)->text();
         if(str.size()==1)
         {
             if(!StackSymbols.contains(str)&&str!="-")
             {
               ui->tableWidget->item(row,column)->setText("");
             }
         }
         if(str.size()>1)
         {
             for(int i=0;i<str.size();i++)
             {
                 if(!StackSymbols.contains(str.at(i)))
                 {
                     ui->tableWidget->item(row,column)->setText("");
                     break;
                 }
             }
         }

     }
     if(column==6)
     {
         QString str= ui->tableWidget->item(row,column)->text();
         if(str!="-")
         {
         for(int i=0;i<str.size();i++)
         {
             if(!SymbolsOut.contains(str.at(i)))
             {
                 ui->tableWidget->item(row,column)->setText("");
                 break;
             }
         }
         }

     }
    ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);
}

void MainWindow::on_lineEdit_symbols_editingFinished()
{
    QString str = ui->lineEdit_symbols->text();
    Symbols = str.split(",");
    Symbols.removeDuplicates();
}

void MainWindow::on_lineEdit_states_editingFinished()
{
    QString str = ui->lineEdit_states->text();
    States = str.split(",");
    States.removeDuplicates();
}

void MainWindow::on_lineEdit_startState_editingFinished()
{

}

void MainWindow::on_lineEdit_stack_editingFinished()
{
    QString str = ui->lineEdit_stack->text();
    StackSymbols = str.split(",");
    StackSymbols.removeDuplicates();
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit_symbols->text();
    Symbols = str.split(",");
    Symbols.removeDuplicates();

    str = ui->lineEdit_states->text();
    States = str.split(",");
    States.removeDuplicates();

    str = ui->lineEdit_stack->text();
    StackSymbols = str.split(",");
    StackSymbols.removeDuplicates();
    if(ui->lineEdit_symbols->text()!="" && ui->lineEdit_states->text()!="" && ui->lineEdit_stack->text()!=""&& ui->lineEdit_finishStates->text()!=""&&ui->lineEdit_startState->text()!="")
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->clearContents();
}

void MainWindow::on_lineEdit_symbolsout_editingFinished()
{
    QString str = ui->lineEdit_symbolsout->text();
    SymbolsOut = str.split(",");
    SymbolsOut.removeDuplicates();
}

void MainWindow::on_lineEdit_stackstart_editingFinished()
{
     stackstart = ui->lineEdit_stackstart->text();
}
