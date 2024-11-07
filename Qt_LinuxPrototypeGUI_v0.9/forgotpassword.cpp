#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>

forgotPassword::forgotPassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::forgotPassword)
{
    ui->setupUi(this);

    /*

    */
}

forgotPassword::~forgotPassword()
{
    delete ui;
}

void forgotPassword::on_pushButton_forgotCancel_clicked()
{
    close();
}

void forgotPassword::on_pushButton_forgotConfirm_clicked()
{
    if (ui->lineEdit_forgotPasswordEmail->text().length() < 7)
    {
        QMessageBox::critical(this, "Email problem", "<font size = 13>Your email is too short.</font>");

    } else if (ui->lineEdit_forgotPasswordEmail->text().contains("@gmail.com") == 0)
    {
        QMessageBox::critical(this, "Email problem", "<font size = 13>Not a valid email.</font>");
    } else
    {
        QMessageBox::information(this, "Email accepted", "<font size = 13>Check your email inbox.</font>");
    }
    // check if in DB
    // send ui->lineEdit_forgotPasswordEmail->text() to client
}
