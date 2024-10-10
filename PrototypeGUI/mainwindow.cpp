#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include <QMessageBox>
#include <QPixmap>
//#include <QtSql>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/ldura/Pictures/qt_pic_1.jpg");
    ui->label_pic->setPixmap(pix.scaled(600,400,Qt::KeepAspectRatio));
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

    // if (client says "yes")
    //     open window
    // else
    //     login failed

    if(username == "test" && password == "test")
    {
        SecDialog secDialog;
        secDialog.setModal(true);
        hide();
        QMessageBox::information(this, "Login", "Login successful. Click OK to proceed");
        secDialog.exec();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Incorrect username or password");
    }
}

