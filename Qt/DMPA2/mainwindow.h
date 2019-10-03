#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMap>
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
    void on_pushButton_addrow_clicked();

    void on_pushButton_deleterow_clicked();

    void on_pushButton_check_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_lineEdit_symbols_editingFinished();

    void on_lineEdit_states_editingFinished();

    void on_lineEdit_startState_editingFinished();

    void on_lineEdit_stack_editingFinished();

    void on_pushButton_clicked();

    void on_lineEdit_symbolsout_editingFinished();

    void on_lineEdit_stackstart_editingFinished();

private:
    Ui::MainWindow *ui;
    QMap <QString,QStringList> rules;
    void PrintResult(QStringList List);
    QStringList States,Symbols,StackSymbols,SymbolsOut;
    QString stackstart;
};

#endif // MAINWINDOW_H
