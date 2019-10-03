#include "changepswd.h"
#include "ui_changepswd.h"
#include "crypter.h"
#include <QString>
#include <QFile>

QString user1;

ChangePswd::ChangePswd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePswd)
{
    ui->setupUi(this);
}

ChangePswd::~ChangePswd()
{
    delete ui;
}
void ChangePswd::setUser(const QString& u)
{
    user1= u;
}
void ChangePswd::on_pushButton_clicked()
{
    QFile file("C:/qt project/sql/login.txt");
    QFile file_temp("C:/qt project/sql/login_temp.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){qDebug("not open");return;}
    if (!file_temp.open(QIODevice::WriteOnly | QIODevice::Text)){qDebug("not open");return;}
    QTextStream in(&file);
    QTextStream out(&file_temp);
    in.setCodec("Unicode");
    out.setCodec("Unicode");
           while(!in.atEnd())
           {
                   QString str = in.readLine();
                   QStringList list = str.split(" ");
                   if(QString::compare(list.at(0),user1, Qt::CaseSensitive)==0)
                   {
                      QString encryptedPassord = Crypter::cryptString(ui->lineEdit->text());
                      out<<user1<<" "<<encryptedPassord<<"\n";
                   }
                   else
                   {
                       out<<str<<"\n";
                   }
                   //QString encryptedString = Crypter::cryptString("Here string you want to encrypt");
                  // QString decryptedString = Crypter::decryptString(encryptedString);
           }
       file.remove();
       file_temp.rename("C:/qt project/sql/login.txt");
       file.close();
       file_temp.close();
       close();
}
