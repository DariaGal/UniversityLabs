#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "stringsgenerator.h"
#include <QListWidget>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void SetRules(QMap<QString,QStringList> Rules1,QMap<QString,QStringList> Rules2,QStringList NoTerm,QStringList NewNoTerm,QStringList Term, QString StartT,QString NewStartT);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_delete1_clicked();

    void on_pushButton_delete2_clicked();

    void on_pushButton_add1_clicked();

    void on_pushButton_add2_clicked();

private:
    Ui::Dialog *ui;
    QMap<QString,QStringList> Rules,NewRules;
    QStringList NoTerm,NewNoTerm,Term;
    QString StartT,NewStartT;
    void print(QStringList List, QListWidget *lw);
    static bool MyLessThan(const QString &s1, const QString &s2);
    void generate();
    void equal();
};

#endif // DIALOG_H
