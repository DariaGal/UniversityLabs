#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QCryptographicHash>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    long long N,r;
    QMap<int,long long> C,D;
    struct banknote{
        int rating;
        long long n;
        QList<long long> s;
    };
        QVector <banknote> money;
    QList<long long> ToBank(QList<long long> n, int b);
    QVector<int> divM(int sum);
private slots:
    void on_pushButton_get_clicked();

    void on_pushButton_check_clicked();

private:
    void GetBanknote(QVector<int> M);
    void CheckBanknote();
    int Bill;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
