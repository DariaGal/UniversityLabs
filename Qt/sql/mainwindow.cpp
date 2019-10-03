#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "changepswd.h"
#include "addnewuser.h"
#include "dialog.h"
#include <QSqlTableModel>
#include <QtSql/QSql>
#include <QString>
#include <QTextStream>
#include <QSqlRecord>

QSqlDatabase db;
QString user_;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\qt project\\bd\\test.db");
    if(db.open())
        qDebug("ok");
    else
        qDebug("cannot open");
    QSqlTableModel *model = new QSqlTableModel(0, db);
    model->setTable("Build");
    model->select();
    ui->tableView->setModel(model);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Search()));
    QObject::connect(ui->action_2, SIGNAL(triggered()), this, SLOT(ChangePassword()));
    QObject::connect(ui->action, SIGNAL(triggered()), this, SLOT(ChangeUser()));
    QObject::connect(ui->action_4, SIGNAL(triggered()), this, SLOT(NewUser()));

}
void MainWindow::Search()
{
    QString str;
    QTextStream (&str)<<"SELECT * FROM Build WHERE "<<ui->comboBox->currentText()<<" LIKE '" << ui->lineEdit->text() << "%'";
    QSqlQueryModel *query;
        query = new QSqlQueryModel();
        query->setQuery(str);
        ui->tableView->setModel(query);
}
void MainWindow::setUser(const QString& u)
{
    user_ = u;
    if(QString::compare(user_,"admin",Qt::CaseSensitive)!=0)
    {
        ui->action_4->setEnabled(false);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}
void MainWindow::ChangePassword()
{
    ChangePswd *dg = new ChangePswd();
    dg->setUser(user_);
    dg->show();
}
void MainWindow::ChangeUser()
{
    Dialog *dg = new Dialog();
    dg->show();
    db.close();
    close();
}
void MainWindow::NewUser()
{
    AddNewUser *dg = new AddNewUser();
    dg->show();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = "INSERT INTO Build (Наименование,Этап,Стоимость,Количество)"
            "VALUES(' ',' ',' ',' ');";
    QSqlQueryModel *query;
    query = new QSqlQueryModel();
    query->setQuery(str);
    ui->tableView->setModel(query);
    QSqlTableModel *model = new QSqlTableModel(0, db);
    model->setTable("Build");
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
{
    QModelIndexList indexes =  ui->tableView->selectionModel()->selectedRows();
    int countRow = indexes.count();

    for( int i = countRow; i > 0; i--)
    ui->tableView->model()->removeRow(indexes.at(i-1).row());

    QSqlTableModel *model = new QSqlTableModel(0, db);
    model->setTable("Build");
    model->select();
    ui->tableView->setModel(model);
}
