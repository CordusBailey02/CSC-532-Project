#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "secdialog.h" // for modalless method
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_createAcc_clicked();

    void on_pushButton_forgotPw_clicked();

    void on_lineEdit_username_returnPressed();

    void on_lineEdit_password_returnPressed();

private:
    Ui::MainWindow *ui;
    //SecDialog *secDialog;
};
#endif // MAINWINDOW_H
