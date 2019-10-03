#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUser(const QString& user);
private slots:
       void Search();
       void ChangePassword();
       void ChangeUser();
       void NewUser();
       void on_pushButton_2_clicked();

       void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString user;

};

#endif // MAINWINDOW_H
