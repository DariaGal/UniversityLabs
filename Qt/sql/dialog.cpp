#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "crypter.h"
#include "forgotpassword.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>


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

void Dialog::on_pushButton_clicked()
{
    bool login=false;
    QFile file("C:/qt project/sql/login.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){qDebug("not open");return;}
    QTextStream in(&file);
    in.setCodec("Unicode");
           while(!in.atEnd())
           {
                   QString str = in.readLine();
                   QStringList list = str.split(" ");
                   if(QString::compare(list.at(0),ui->lineEdit->text(), Qt::CaseSensitive)==0)
                   {
                       if(QString::compare(Crypter::decryptString(list.at(1)),ui->lineEdit_2->text(), Qt::CaseSensitive)==0)
                       {
                           login=true;
                           MainWindow *dg = new MainWindow();
                           dg->setUser(list.at(0));
                           dg->show();
                           close();
                           break;
                       }
                   }

           }
           if(!login)
           {
           QMessageBox msgBox;
           msgBox.setText("Неверный логин или пароль");
           msgBox.exec();
           }
        file.close();


}

void Dialog::on_pushButton_2_clicked()
{
    bool login=false;
    QFile file("C:/qt project/sql/login.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){qDebug("not open");return;}
    QTextStream in(&file);
    in.setCodec("Unicode");
           while(!in.atEnd())
           {
                   QString str = in.readLine();
                   QStringList list = str.split(" ");
                   if(QString::compare(list.at(0),ui->lineEdit->text(), Qt::CaseSensitive)==0)
                   {
                           login=true;
                           ForgotPassword *dg = new ForgotPassword();
                           dg->setUser(list.at(0));
                           dg->show();
                           close();
                           break;

                   }

           }
           if(!login)
           {
           QMessageBox msgBox;
           msgBox.setText("Неверный логин");
           msgBox.exec();
           }
        file.close();
}
