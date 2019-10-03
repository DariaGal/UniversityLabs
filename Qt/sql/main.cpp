#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
