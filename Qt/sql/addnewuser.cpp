#include "addnewuser.h"
#include "ui_addnewuser.h"
#include "crypter.h"
#include <QFile>
#include <QTextStream>

AddNewUser::AddNewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewUser)
{
    ui->setupUi(this);
}

AddNewUser::~AddNewUser()
{
    delete ui;
}

void AddNewUser::on_pushButton_clicked()
{
    QFile file("C:/qt project/sql/login.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)){qDebug("not open");return;}
    QTextStream out(&file);
    out.setCodec("Unicode");
    out<<ui->lineEdit->text()<<" "<<Crypter::cryptString(ui->lineEdit_2->text())<<" "<<ui->lineEdit_3->text()<<"\n";
    file.close();
    close();
}
