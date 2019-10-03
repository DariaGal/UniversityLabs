#ifndef CHANGEPSWD_H
#define CHANGEPSWD_H

#include <QDialog>

namespace Ui {
class ChangePswd;
}

class ChangePswd : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePswd(QWidget *parent = 0);
    ~ChangePswd();
    void setUser(const QString& user);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePswd *ui;
    QString user;
};

#endif // CHANGEPSWD_H
