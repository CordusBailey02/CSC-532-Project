#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include <QMessageBox>

forgotPassword::forgotPassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::forgotPassword)
{
    ui->setupUi(this);
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
    if (ui->lineEdit_forgotPasswordEmail->text().contains("@gmail.com") == 0)
    {
        QMessageBox::critical(this, "Email problem", "Not a valid email");
    }
    // check if in DB
}

