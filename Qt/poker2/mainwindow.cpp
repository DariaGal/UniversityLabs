#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "lab1.h"
#include <time.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{

    int NumPl,NumKP,NumKT,NumKards;
    NumPl = ui->spinBox_players->value();
    NumKP = ui->spinBox_kards->value();
    NumKT = ui->spinBox_table->value();
    NumKards = NumPl*NumKP+NumKT;
    ui->textEdit->append("количество игроков ="+QString::number(NumPl) + ", карт у игроков ="+QString::number(NumKP)+", карт на столе ="+QString::number(NumKT));
    int *kards = new int[52];
    kards = CreateKards(kards);
    long long p = GetSimple();
    Player players [NumPl+1];
     for(int i=0;i<NumPl+1;i++)
     {
         players[i].Init(p);
     }

    for(int i=0;i<NumPl+1;i++)
    {
        kards = players[i].CryptAndMix(kards, 52);
        ui->textEdit->append("игрок "+QString::number(i)+" зашифровал и перемешал колоду");
    }

     int n=0;
     for(int i=1;i<NumPl+1;i++)
     {
         QString str;
          for(int j=0;j<NumKP;j++)
         {
             players[i].SetKards(kards[n]);
             str.append(QString::number(kards[n])+" ");
             kards[n]=0;
             n++;
         }
            ui->textEdit->append("игрок "+QString::number(i)+" получил "+QString::number(NumKP)+"шт. зашифрованных карт:");
             ui->textEdit->append("("+str+")");
     }
     QString str;
     while(n<NumKards)
     {

         str.append(QString::number(kards[n])+" ");
         players[0].SetKards(kards[n]);
         n++;
     }
      ui->textEdit->append("стол получил "+QString::number(NumKT)+"шт. зашифрованных карт:");
      ui->textEdit->append("("+str+")");
     delete kards;
     QList<int> sendK;
     for(int i=0;i<NumPl+1;i++)
     {

         sendK = players[i].GetKards();
         ui->textEdit->append("дешифрация карт игрока "+QString::number(i));
        for(int j=0;j<NumPl+1;j++)
        {
            if(i!=j)
            {
                ui->textEdit->append("игрок "+QString::number(j)+" дешифровал карты игрока "+QString::number(i));
                sendK = players[j].EncryptKards(sendK);
            }
        }
        sendK = players[i].EncryptKards(sendK);
        players[i].SetKards(sendK);
        QString str;
        QDebug dStream(&str);
        dStream << sendK;
        ui->textEdit->append("игрок "+QString::number(i)+" получил карты "+str);
     }
     ShowCards(players,NumPl,NumKT,NumKP);
}

int* MainWindow::CreateKards(int * k)
{
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(52);
    int i=0;
    //int *all = new int [52];
    for(int n=2;n<15;n++)
    {
        for(int m=1;m<=4;m++)
        {
            k[i] = m*100+n;

            qDebug()<<k[i];
            i++;
        }
    }
    i=0;
    while(i<52)
    {
            QImage *img = new QImage(":/k/"+QString::number(k[i])+".png");
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img));

            ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(k[i])));
            ui->tableWidget->setItem(0,i,item);
            i++;

    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    return k;
}
void MainWindow::ShowCards(Player *p,int NumPl, int T,int P)
{
    ui->tableWidget_2->setRowCount(NumPl+1);
    if(T>P)
     ui->tableWidget_2->setColumnCount(T);
    else ui->tableWidget_2->setColumnCount(P);
    ui->tableWidget_2->setVerticalHeaderItem(0,new QTableWidgetItem("стол"));
    for(int i=1;i<NumPl+1;i++)
    {
        ui->tableWidget_2->setVerticalHeaderItem(i,new QTableWidgetItem("игрок "+QString::number(i)));
    }
    for(int i=0;i<NumPl+1;i++)
    {
        QList<int> k = p[i].GetKards();
        qDebug()<<k;
        int n = k.size();
        for(int j=0;j<n;j++)
        {
            QImage *img = new QImage(":/k/"+QString::number(k.at(j))+".png");
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(60,83));
            ui->tableWidget_2->setItem(i,j,item);
        }
    }
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->resizeRowsToContents();
}
