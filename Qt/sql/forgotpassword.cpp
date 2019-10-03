#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
QString user2;
ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
}
void ForgotPassword::setUser(const QString& u)
{
    user2 = u;
}
ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_pushButton_clicked()
{
    bool word=false;
    QFile file("C:/qt project/sql/login.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){qDebug("not open");return;}
    QTextStream in(&file);
    in.setCodec("Unicode");
           while(!in.atEnd())
           {
                   QString str = in.readLine();
                   QStringList list = str.split(" ");
                   if(QString::compare(list.at(0),user2, Qt::CaseSensitive)==0)
                   {
                       if(QString::compare(list.at(2),ui->lineEdit->text(), Qt::CaseSensitive)==0)
                       {
                           word=true;
                           MainWindow *dg = new MainWindow();
                           dg->setUser(list.at(0));
                           dg->show();
                           close();
                           break;
                       }

                   }

           }
           if(!word)
           {
           QMessageBox msgBox;
           msgBox.setText("Неверное секретное слово");
           msgBox.exec();
           }
        file.close();
}
