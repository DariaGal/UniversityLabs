#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include<QComboBox>
#include<QLabel>

#include "stringsgenerator.h"
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_StartTerm_editingFinished();

    void on_lineEdit_NoTerm_editingFinished();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QLineEdit *lineEditArray[10];
    QLabel *labelRule[10];
    QLabel *point[10];
    int ruleCount;
    QStringList Term;
    QStringList NoTerm;
    QString StartTerm;
    QString RuleTable[10][2];
    StringsGenerator *G;
    QMap <QString,QStringList> Rules;
    void PrintResult(QStringList List);
    static bool MyLessThan(const QString &s1, const QString &s2);
    int fromN,toN;
    bool isCreate;

};

#endif // MAINWINDOW_H
