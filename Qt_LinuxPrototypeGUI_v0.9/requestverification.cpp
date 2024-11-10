#include "requestverification.h"
#include "ui_requestverification.h"
#include <QtWidgets>

requestVerification::requestVerification(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::requestVerification)
{
    ui->setupUi(this);
}

requestVerification::~requestVerification()
{
    delete ui;
}

void requestVerification::on_pushButton_addResume_clicked()
{
    QString filepath_resume=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf)");
    if (filepath_resume == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_resume);
        //int sendInt = send(int socket, filepath_resume, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_addDegree_clicked()
{
    QString filepath_degree=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_degree == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_degree);
        //int sendInt = send(int socket, filepath_degree, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_addCertificate_clicked()
{
    QString filepath_certificates=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png);;   JPEG File(*.jpg)");
    if (filepath_certificates == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_certificates);
        //int sendInt = send(int socket, filepath_certificates, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_addDriverLicense_clicked()
{
    QString filepath_driversLicense=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_driversLicense == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_driversLicense);
        //int sendInt = send(int socket, filepath_driversLicense, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_submitVerificationRequest_clicked()
{
    QMessageBox::information(this, "Request Received", "<font size = 13>Your verification request has been submitted.</font>");
}


void requestVerification::on_pushButton_cancelVerificationRequest_clicked()
{
    close();
}

