#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QMap>
#include "grammarconverter.h"
#include "dialog.h"
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
    void on_lineEdit_alph_editingFinished();

    void on_lineEdit_neterm_editingFinished();

    void on_lineEdit_start_editingFinished();

    void on_pushButton_addrule_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_deleterule_clicked();

    void on_pushButton_clicked();
    void Author();
    void Theme();
    void Open();

    void on_pushButton_saveGram_clicked();

private:
    Ui::MainWindow *ui;
    QStringList Term,NoTerm;
    QString StartS;
    QMap<QString,QStringList> Rules,NewRules;
    void test(QString str,QStringList W);
    void PrintResult(QStringList List);
    void SavetoFile();
    void startEqual();
};

#endif // MAINWINDOW_H
