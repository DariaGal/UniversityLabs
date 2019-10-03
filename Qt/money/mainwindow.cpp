#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lab1.h"
#include "lab2.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int B[11] = {1,2,5,10,50,100,200,500,1000,2000,5000};
    long long P=GetSimple();
    long long Q=GetSimple();
    long long f=(P-1)*(Q-1);
    N=P*Q;
    for(int i = 0; i<11 ; i++)
    {
        long long d,c;
        GetCD(f,d,c);
        C[B[i]] = c;
        D[B[i]] = d;
    }
    while(1)
    {
        r = (rand()%(N-2))+2;
        if(GCD(r, N)==1) break;
    }
    Bill = 25000;
    ui->label_money->setText("На счету "+QString::number(Bill)+" руб.");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_get_clicked()
{
    int sum = ui->lineEdit->text().toInt();
    if(sum<Bill)
    {
        Bill = Bill - sum;
        ui->textEdit->setText("Сумма"+QString::number(sum));
        QVector<int> m = divM(sum);
        ui->label_money->setText("На счету "+QString::number(Bill)+" руб.");
        GetBanknote(m);
    }
    else
    {
        ui->textEdit->setText("Запрошена слишком большая сумма");
    }

}
void MainWindow::GetBanknote(QVector<int> M)
{
   money.clear();
   for(int j = 0; j<M.size();j++)
   {
        long long n1 = (rand()%(N-2))+2;
        QByteArray h = QByteArray(QCryptographicHash::hash(QByteArray::number(n1),QCryptographicHash::Md5).toHex());
        int Bnknt = M.at(j);
        ui->textEdit->append("Купюра: "+QString::number(Bnknt)+"\t номер:"+QString::number(n1)+"\t хэш: "+h);
        ui->textEdit->append("Вычисляем n\'");
        QList <long long> n;
        foreach(int i ,h)
        {
            n << ((i%N)*ModExp(r,D[Bnknt],N))%N;
        }
        ui->textEdit->append("Отправляем в банк на подпись");
        QList<long long> s1 = ToBank(n,Bnknt);

        ui->textEdit->append("Банк подписал купюру и отправил обратно");
        long long x,gcd,r1;
        Euclid(N,r,x,r1,gcd);
        if(r1<0)
        {
          r1=r1+N;
        }
        QList<long long> s;
        ui->textEdit->append("Вычисляем s");
        banknote b;
        foreach(long long i ,s1)
        {
            b.s<<(ModExp(i,1,N)*ModExp(r1,1,N))%N;
        }
        b.n = n1;
        b.rating = Bnknt;
        money.insert(money.size(), b);
        ui->textEdit->append("Купюра подписана\n");
   }
   ui->textEdit->append("Все банкноты имеют подписи и готовы к использованию");

   QTextCursor c = ui->textEdit->textCursor();
   c.movePosition(QTextCursor::End);
   ui->textEdit->setTextCursor(c);

}
QList<long long> MainWindow::ToBank(QList<long long> n, int b)
{
    QList<long long> s;
    foreach(long long i, n)
    {
        s<<ModExp(i,C[b],N);
    }
    return s;
}
QVector<int> MainWindow::divM(int sum)
{
    int  i = 0;
    int B[11] = {5000,2000,1000,500,200,100,50,10,5,2,1};
    QVector<int> m;
    QString w("купюры: ");
    while(i<11)
    {
        int s = sum/B[i];
        if(s>=1)
        {
            sum = sum - B[i];
            m.append(B[i]);
            w.append(QString::number(B[i])+" ");
            if(sum==0){break;}
        }
        else{i++;}
    }
    ui->textEdit->append(w);
    return m;
}
void MainWindow::CheckBanknote()
{
    bool f=true;
    ui->textEdit->append("\nПроверка банкнот");
    for(int i=0;i<money.size();i++)
    {
        QByteArray h = QByteArray(QCryptographicHash::hash(QByteArray::number(money.at(i).n),QCryptographicHash::Md5).toHex());
        QByteArray res;
        foreach(long long e, money.at(i).s)
        {
            res.append( ModExp(e,D[money.at(i).rating],N));
        }

        ui->textEdit->append("Банкнота: номер "+QString::number(money.at(i).n)+" номинал "+QString::number(money.at(i).rating));
        if(res == h)
        {
             ui->textEdit->append("Является подлинной "+h+"=="+res+"\n");
        }
        else
        {
            ui->textEdit->append("Поддельная "+h+"!="+res+"\n");
            f=false;
        }
    }
    if(f)
    {
        ui->textEdit->append("Все банкноты подлинные");
    }
}

void MainWindow::on_pushButton_check_clicked()
{
    CheckBanknote();
    ui->lineEdit->clear();

}
