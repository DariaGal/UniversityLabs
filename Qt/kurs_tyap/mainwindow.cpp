#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_autor, SIGNAL(triggered()), this, SLOT(Author()));
    connect(ui->action_theme, SIGNAL(triggered()), this, SLOT(Theme()));
    connect(ui->action_open, SIGNAL(triggered()), this, SLOT(Open()));
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->horizontalHeader()->resizeSection(0,50);
    ui->tableWidget->horizontalHeader()->resizeSection(1,45);
    ui->tableWidget->horizontalHeader()->resizeSection(2,130);
    ui->tableWidget->horizontalHeader()->hide();

    ui->tableWidget_2->setColumnCount(3);
    ui->tableWidget_2->horizontalHeader()->resizeSection(0,50);
    ui->tableWidget_2->horizontalHeader()->resizeSection(1,45);
    ui->tableWidget_2->horizontalHeader()->resizeSection(2,200);
    ui->tableWidget_2->horizontalHeader()->hide();
    ui->lineEdit_alph_2->setReadOnly(true);
    ui->lineEdit_neterm_2->setReadOnly(true);
    ui->lineEdit_start_2->setReadOnly(true);
}
void MainWindow::Author()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Автор");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Галиуллина Дарья, ИП-313, 4 курс");
    msgBox.exec();
}
void MainWindow::Theme()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Тема");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Задана произвольная контекстно-свободная грамматика. Выполнить преобразование ее к каноническому виду. Преобразование осуществлять поэтапно, отображая результат на каждом из этапов. Проверить построенную грамматику на эквивалентность исходной: по обеим грамматикам сгенерировать множества всех цепочек в заданном пользователем диапазоне длин и проверить их на идентичность.");
    msgBox.exec();
}
void MainWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./examples",
           tr("Text Files (*.txt)"));

       if (fileName != "") {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
               return;
           }
           ui->textEdit->clear();
           ui->lineEdit_alph_2->clear();
           ui->lineEdit_neterm_2->clear();
           ui->lineEdit_start_2->clear();
           ui->tableWidget_2->clear();
           ui->tableWidget_2->setRowCount(0);
           ui->tableWidget->clear();
           ui->tableWidget->setRowCount(0);
           QTextStream in(&file);
           int l = 0;
              while (!in.atEnd())
              {
                 QString line = in.readLine();
                 if(l==0){
                     Term = line.split(",");
                     ui->lineEdit_alph->setText(line);}
                 if(l==1){
                     NoTerm = line.split(",");
                     ui->lineEdit_neterm->setText(line);}
                 if(l==2){
                     StartS = line;
                     ui->lineEdit_start->setText(line);}
                 if(l>2)
                 {
                     QStringList list = line.split("->");
                     int row =  ui->tableWidget->rowCount();
                     ui->tableWidget->insertRow(row);
                     QComboBox* C = new QComboBox(ui->tableWidget);
                     C->addItems(NoTerm);
                     C->setCurrentText(line.at(0));
                     ui->tableWidget->setCellWidget(row,0,C);
                     QTableWidgetItem *item = new QTableWidgetItem("->");
                     item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                     ui->tableWidget->setItem(row,1,item);
                     ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
                     QTableWidgetItem *itm = new QTableWidgetItem(list.at(1));
                     ui->tableWidget->setItem(row,2,itm);
                 }
                 l++;
              }
       }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_alph_editingFinished()
{
    QString str = ui->lineEdit_alph->text();
    Term = str.split(",");
    Term.removeDuplicates();
}

void MainWindow::on_lineEdit_neterm_editingFinished()
{
    QString str = ui->lineEdit_neterm->text();
    NoTerm = str.split(",");
    NoTerm.removeDuplicates();
}

void MainWindow::on_lineEdit_start_editingFinished()
{
    StartS = ui->lineEdit_start->text();
}
void MainWindow::on_pushButton_deleterule_clicked()
{
     ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}
void MainWindow::on_pushButton_addrule_clicked()
{
    if(NoTerm.isEmpty()||Term.isEmpty()||StartS=="")
    {
        ui->pushButton->setEnabled(false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не все поля заполнены");
        msgBox.exec();
    }else{
     int row =  ui->tableWidget->rowCount();
     ui->tableWidget->insertRow(row);
     QComboBox* C = new QComboBox(ui->tableWidget);
     C->addItems(NoTerm);
     ui->tableWidget->setCellWidget(row,0,C);
     ui->tableWidget->setItem(row,1,new QTableWidgetItem("->"));
     ui->tableWidget->setItem(row,2,new QTableWidgetItem(""));
     ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    if(NoTerm.isEmpty()||Term.isEmpty()||StartS=="")
    {
        ui->pushButton->setEnabled(false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не все поля заполнены");
        msgBox.exec();
     }else{
        Rules.clear();
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            QComboBox *myCB = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));
            QString NT = myCB->currentText();
            QString str = ui->tableWidget->item(i,2)->text();
            if(str!="")
            {
            QStringList list = str.split("|");

                if(Rules.contains(NT))
                {
                   Rules[NT] = Rules[NT] + list;
                }
                else
                {
                     Rules[NT] = list;
                }
            }
        }
        if(Rules.isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Правила не заданы");
            msgBox.exec();
        }else{
                GrammarConverter conv(Rules,StartS,Term,NoTerm);
                QStringList result;

                qDebug()<<conv.RemoveUselessSymbols(result);
                qDebug()<<conv.RemoveUnattainableSymbols(result);
                qDebug()<<conv.RemoveEmptyRules(result);
                qDebug()<<conv.RemoveLoopRules(result);
                PrintResult(result);
                QString NewStartTerm,t;
                QStringList NewNoTerm;
                NewRules = conv.GetNewGram(NewStartTerm,NewNoTerm);
                foreach (QString s, NewNoTerm) {
                    t.append(s+",");
                }
                t.remove(t.size()-1,1);
                ui->lineEdit_neterm_2->setText(t);
                ui->lineEdit_alph_2->setText(ui->lineEdit_alph->text());
                ui->lineEdit_start_2->setText(NewStartTerm);

                ui->tableWidget_2->clear();
                ui->tableWidget_2->setRowCount(0);
                for(auto r : NewRules.keys())
                {
                    int row =  ui->tableWidget_2->rowCount();
                    ui->tableWidget_2->insertRow(row);
                    QComboBox* C = new QComboBox(ui->tableWidget_2);
                    C->addItem(r);
                    ui->tableWidget_2->setCellWidget(row,0,C);
                    QTableWidgetItem *item = new QTableWidgetItem("->");
                    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                    ui->tableWidget_2->setItem(row,1,item);
                    ui->tableWidget_2->item(row,1)->setTextAlignment(Qt::AlignCenter);
                    QString l;
                    foreach (QString s, NewRules.value(r)) {
                        l.append(s+"|");
                    }
                    l.remove(l.size()-1,1);
                    QTableWidgetItem *itm = new QTableWidgetItem(l);
                    itm->setFlags(itm->flags() ^ Qt::ItemIsEditable);
                    ui->tableWidget_2->setItem(row,2,itm);
                }
            ui->pushButton->setEnabled(true);
            if(ui->action_save->isChecked()){
                qDebug()<<"op";
                SavetoFile();}
        }
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

void MainWindow::startEqual()
{
    Rules.clear();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QComboBox *myCB = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));
        QString NT = myCB->currentText();
        QString str = ui->tableWidget->item(i,2)->text();
        QStringList list = str.split("|");
        if(Rules.contains(NT))
        {
           Rules[NT] = Rules[NT] + list;
        }
        else
        {
             Rules[NT] = list;
        }
    }
    NewRules.clear();
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        QComboBox *myCB = qobject_cast<QComboBox*>(ui->tableWidget_2->cellWidget(i,0));
        QString NT = myCB->currentText();
        QString str = ui->tableWidget_2->item(i,2)->text();
        QStringList list = str.split("|");
        if(NewRules.contains(NT))
        {
           NewRules[NT] = NewRules[NT] + list;
        }
        else
        {
             NewRules[NT] = list;
        }
    }
    QString str = ui->lineEdit_neterm_2->text();
    QStringList NewNoTerm = str.split(",");
    NewNoTerm.removeDuplicates();
    Dialog myDialog( this );
    myDialog.setModal( true );
    myDialog.SetRules(Rules,NewRules,NoTerm,NewNoTerm,Term,StartS,ui->lineEdit_start_2->text());
    myDialog.exec();
}

void MainWindow::on_pushButton_clicked()
{
    startEqual();
}
void MainWindow::SavetoFile()
{
    QString filename = QFileDialog::getSaveFileName(this,"Сохранить результат","./result","Text Files (*.txt)");
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream stream( &file );
        stream << tr("Исходная грамматика:") << endl;
        stream << "G=({"+ui->lineEdit_alph->text()+"},{"+ui->lineEdit_neterm->text()+"},"+ui->lineEdit_start->text()+",P})"<< endl;
        for(auto r : Rules.keys())
        {
            QString l;
            foreach (QString s, Rules.value(r)) {
                l.append(s+"|");
            }
            l.remove(l.size()-1,1);
            stream<<r<<"->"<<l;
        }
        stream << "\n"<<tr("Ход преобразования:")<<"\n" << endl;
        stream << ui->textEdit->toPlainText() << endl;

        file.close();
    }
}

void MainWindow::on_pushButton_saveGram_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Сохранить исходную грамматику","./examples","Text Files (*.txt)");
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        qDebug()<<"open";
        QTextStream stream( &file );
        stream<<ui->lineEdit_alph->text()<<endl;
        stream<<ui->lineEdit_neterm->text()<<endl;
        stream<<ui->lineEdit_start->text()<<endl;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            QComboBox *myCB = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0));
            QString NT = myCB->currentText();
            QString str = ui->tableWidget->item(i,2)->text();
            stream<<NT+"->"+str<<endl;
        }
    }
}
