#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include "createaccount.h"
#include "forgotpassword.h"
#include <QMessageBox>
//#include <QPixmap>
//#include <QtSql>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*

    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_cancel_clicked()
{
    close();
}


void MainWindow::on_pushButton_login_clicked()
{
    /*
    Opening a window through the Modal approach
    Main window cannot be accessed/used after the second window is open.
    Good for login pages where you hit login and that window can be closed.
    There is a modal-less approach where both windows can be used at the same time.
    Might not use for CSC532 project.

    Modalless method:
    Delete #include secdialog.h from this file and make changes in mainwindow.h
    Then:

    secDialog = new SecDialog(this);
    secDialog->show();

    */

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // send to client to send to database to confirm login data

    // send username
    // send password

    // if (client says "yes")
    //     open window
    // else
    //     login failed

    if(username == "test" && password == "test")
    {
        SecDialog secDialog;
        secDialog.setModal(true); // not needed
        hide();
        QMessageBox::information(this, "Login Successful", "Login successful. Click OK to proceed");
        secDialog.exec();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password");
    }
}


void MainWindow::on_pushButton_createAcc_clicked()
{
    createAccount createAccount_1;
    createAccount_1.exec();
}


void MainWindow::on_pushButton_forgotPw_clicked()
{
    forgotPassword forgotPassword_1;
    forgotPassword_1.exec();
}


void MainWindow::on_lineEdit_username_returnPressed()
{
    ui->lineEdit_password->setFocus();
}


void MainWindow::on_lineEdit_password_returnPressed()
{
    on_pushButton_login_clicked();
}
