#include "createaccount.h"
#include "ui_createaccount.h"
#include "AccountCode.h"
#include <QMessageBox>

createAccount::createAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createAccount)
{
    ui->setupUi(this);
    ui->lineEdit_accountNewEmail->setFocus();
    ui->pushButton_createConfirm->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_createCancel->setFocusPolicy(Qt::NoFocus);

    ui->lineEdit_accountNewPassword->setMaxLength(15);
    ui->lineEdit_accountNewPasswordConfirm->setMaxLength(15);
    ui->lineEdit_accountNewEmail->setMaxLength(40);
    ui->lineEdit_accountNewUsername->setMaxLength(15);

    /*

    */
}

createAccount::~createAccount()
{
    delete ui;
}

void createAccount::on_pushButton_createCancel_clicked()
{
    close();
}


void createAccount::on_pushButton_createConfirm_clicked()
{
    // if statements to check newPassword and newPasswordConfirm are equal
    if (ui->lineEdit_accountNewEmail->text().length() < 7)
    {
        QMessageBox::critical(this, "Email problem", "Your email is too short");

        // search DB for email
        // *send to client* ui->lineEdit_accountNewEmail->text();
        // QString emailFromDB = *email from client*
        // else if (ui->lineEdit_accountNewEmail->text().compare(emailFromDB) == 0)
        //QMessageBox::critical(this, "Email problem", "Your email already exists");

    } else if (!(ui->lineEdit_accountNewEmail->text().contains("@gmail.com")))
    {
        QMessageBox::critical(this, "Email problem", "Not a valid email");

    } else if (ui->lineEdit_accountNewUsername->text().length() < 4)
    {
        QMessageBox::critical(this, "Username problem", "Your username is too short");

        // search DB for username
        // *send to client* ui->lineEdit_accountNewUsername->text();
        // QString usernameFromDB = *username from client*
        // else if (ui->lineEdit_accountNewUsername->text().compare(usernameFromDB) == 0)
        //QMessageBox::critical(this, "Username problem", "Your username is too short");

    } else if (ui->lineEdit_accountNewPassword->text().length() < 8)
    {
        QMessageBox::critical(this, "Password problem", "Your password is too short");

    } else if ( ui->lineEdit_accountNewPassword->text().length() != ui->lineEdit_accountNewPasswordConfirm->text().length() ||
               ui->lineEdit_accountNewPassword->text().compare(ui->lineEdit_accountNewPasswordConfirm->text()) != 0)
    {
        QMessageBox::critical(this, "Password problem", "Your passwords do not match");

    } else if (ui->lineEdit_accountNewPassword->text().compare(ui->lineEdit_accountNewPasswordConfirm->text()) == 0)
    {
        QMessageBox::information(this, "Account Created", "Your account was created. Check your email for a verification link with a code.");
    }
    // QString accountNewEmailClient = ui->lineEdit_accountNewEmail->text();


}


void createAccount::on_lineEdit_accountNewEmail_returnPressed()
{
    ui->lineEdit_accountNewUsername->setFocus();
}


void createAccount::on_lineEdit_accountNewUsername_returnPressed()
{
    ui->lineEdit_accountNewPassword->setFocus();
}


void createAccount::on_lineEdit_accountNewPassword_returnPressed()
{
    ui->lineEdit_accountNewPasswordConfirm->setFocus();
}


void createAccount::on_lineEdit_accountNewPasswordConfirm_returnPressed()
{
    on_pushButton_createConfirm_clicked();
}


void createAccount::on_pushButton_AccountCode_clicked()
{
    AccountCode accountCode_1;
    accountCode_1.exec();
}
