#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_createtable_clicked();
    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_check_clicked();

    void on_pushButton_fromFile_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
    QStringList States,Symbols,FinishStates;
    QString StartState;
    void PrintResult(QStringList List);
};

#endif // MAINWINDOW_H
