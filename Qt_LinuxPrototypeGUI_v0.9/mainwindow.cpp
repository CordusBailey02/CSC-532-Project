#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include "createaccount.h"
#include "forgotpassword.h"
#include "main.cpp"
#include <QMessageBox>
//#include <QPixmap>
//#include <QtSql>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //extern QString mySocket;
    //mySocket = mySocket+1;

    //qDebug() << mySocket;
    //ui->label_2->setText(mySocket);
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
        //secDialog.setModal(true); // not needed
        hide();
        QMessageBox::information(this, "Login Successful", "<font size = 13>Login successful. Click OK to proceed</font>");
        secDialog.showMaximized();
        secDialog.exec();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "<font size = 13>Incorrect username or password</font>");
    }

    /*
     // Convert the QString to char*
    std::string username_str = username.toStdString();
    char* username_c_str = new char[username_str.size() + 1];
    strcpy(username_c_str, username_str.c_str());

    std::string password_str = password.toStdString();
    char* password_c_str = new char[password_str.size() + 1];
    strcpy(password_c_str, password_str.c_str());

    // Get Length of the username and password
    size_t username_size = username_str.size();
    size_t password_size = password_str.size();

    //Request struct
    struct request_header outbound_request_header;

    // Send login attempt to client
    bool login_attempt = gui_send_login_attempt(client_tcp_socket, &outbound_request_header, username_c_str, username_size, password_c_str, password_size);

    if(login_attempt)
    {
        SecDialog secDialog;
        //secDialog.setModal(true); // not needed
        hide();
        QMessageBox::information(this, "Login Successful", "<font size = 13>Login successful. Click OK to proceed</font>");
        secDialog.showMaximized();
        secDialog.exec();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "<font size = 13>Incorrect username or password</font>");
    }
    */
}


void MainWindow::on_pushButton_createAcc_clicked()
{
    createAccount createAccount_1;
    createAccount_1.showMaximized();
    createAccount_1.exec();
}


void MainWindow::on_pushButton_forgotPw_clicked()
{
    forgotPassword forgotPassword_1;
    forgotPassword_1.showMaximized();
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
