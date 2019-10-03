#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
}
void Dialog::SetRules(QMap<QString,QStringList> Rules1,QMap<QString,QStringList> Rules2,QStringList NoTerm,QStringList NewNoTerm,QStringList Term, QString StartT,QString NewStartT)
{
    qDebug()<<Rules1;
    qDebug()<<Rules2;
    Rules = Rules1;
    NewRules = Rules2;
    this->NoTerm = NoTerm;
    this->NewNoTerm = NewNoTerm;
    this->Term = Term;
    this->NewStartT = NewStartT;
    this->StartT = StartT;
}
void Dialog::print(QStringList List, QListWidget *lw)
{
    lw->clear();
    qSort(List.begin(), List.end(), MyLessThan);
    for(int i = 0; i<List.size();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(List.at(i));
        item->setFlags( item->flags() | Qt::ItemIsEditable );
        lw->addItem(item);
    }
}
bool Dialog::MyLessThan(const QString &s1, const QString &s2)
{
  if(s1.size()==s2.size())
  {
     return (s1 < s2);
  }
  else
  {
      return (s1.size() < s2.size());
  }
}
void Dialog::generate()
{
    int fromN=ui->spinBox_from->value();
    int toN=ui->spinBox_to->value();
    QStringList NoTermsEmpty;
    for(auto r : Rules.keys())
    {
        if(Rules.value(r).contains("~"))
        {
            NoTermsEmpty.append(r);
        }
    }
    StringsGenerator G1;
    G1.SetParemeters(Term,NoTerm,Rules,StartT,fromN,toN);
    G1.Start(NoTermsEmpty);
    print(G1.Print(),ui->listWidget_1);

    NoTermsEmpty.clear();
    for(auto r : NewRules.keys())
    {
        if(NewRules.value(r).contains("~"))
        {
            NoTermsEmpty.append(r);
        }
    }
    StringsGenerator G2;
    G2.SetParemeters(Term,NewNoTerm,NewRules,NewStartT,fromN,toN);
    G2.Start(NoTermsEmpty);
    print(G2.Print(),ui->listWidget_2);
    ui->textEdit->clear();
}

void Dialog::on_pushButton_3_clicked()
{
   generate();
}
void Dialog::equal()
{
    for(int i=0;i<ui->listWidget_1->count();i++)
    {

           ui->listWidget_1->item(i)->setBackgroundColor(Qt::white);

    }
    for(int i=0;i<ui->listWidget_2->count();i++)
    {

           ui->listWidget_2->item(i)->setBackgroundColor(Qt::white);

    }
    QStringList l1,l2,lt;
    for(int i=0;i<ui->listWidget_1->count();i++)
    {
       l1.append(ui->listWidget_1->item(i)->text());
    }
    for(int i=0;i<ui->listWidget_2->count();i++)
    {
       l2.append(ui->listWidget_2->item(i)->text());
    }
    lt = l1;
    foreach (QString s, l1) {
        if(l2.contains(s)){
            l2.removeOne(s);
            lt.removeOne(s);
        }
    }
    if(l2.isEmpty()&&lt.isEmpty())
    {
        ui->textEdit->setText("Все цепочки совпали");
    }
    else
    {
        ui->textEdit->setText("Цепочки не совпали");
        for(int i=0;i<ui->listWidget_1->count();i++)
        {
           if(lt.contains(ui->listWidget_1->item(i)->text()))
           {
               ui->listWidget_1->item(i)->setBackgroundColor(Qt::red);
           }
        }
        for(int i=0;i<ui->listWidget_2->count();i++)
        {
           if(l2.contains(ui->listWidget_2->item(i)->text()))
           {
               ui->listWidget_2->item(i)->setBackgroundColor(Qt::red);
           }
        }
    }
}

void Dialog::on_pushButton_clicked()
{
   equal();
}

void Dialog::on_pushButton_delete1_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget_1->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget_1->takeItem(ui->listWidget_1->row(item));
    }
}

void Dialog::on_pushButton_delete2_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
    }
}

void Dialog::on_pushButton_add1_clicked()
{
    QListWidgetItem *item = new QListWidgetItem("");
    item->setFlags( item->flags() | Qt::ItemIsEditable );
    ui->listWidget_1->addItem(item);
}

void Dialog::on_pushButton_add2_clicked()
{
    QListWidgetItem *item = new QListWidgetItem("");
    item->setFlags( item->flags() | Qt::ItemIsEditable );
    ui->listWidget_2->addItem(item);
}
