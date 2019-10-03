#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = 0);
    ~ForgotPassword();
    void setUser(const QString& user);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ForgotPassword *ui;
    QString user;
};

#endif // FORGOTPASSWORD_H
