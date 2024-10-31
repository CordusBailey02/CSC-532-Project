#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>

namespace Ui {
class createAccount;
}

class createAccount : public QDialog
{
    Q_OBJECT

public:
    explicit createAccount(QWidget *parent = nullptr);
    ~createAccount();

private slots:
    void on_pushButton_createCancel_clicked();

    void on_pushButton_createConfirm_clicked();

    void on_lineEdit_accountNewEmail_returnPressed();

    void on_lineEdit_accountNewUsername_returnPressed();

    void on_lineEdit_accountNewPassword_returnPressed();

    void on_lineEdit_accountNewPasswordConfirm_returnPressed();

    void on_pushButton_AccountCode_clicked();

private:
    Ui::createAccount *ui;
};

#endif // CREATEACCOUNT_H
