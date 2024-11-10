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
        ui->label_resumeFilePath->setText(filepath_resume);
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
        ui->label_degreeFilePath->setText(filepath_degree);
        //int sendInt = send(int socket, filepath_degree, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_addCertificate_clicked()
{
    QString filepath_certificate=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png);;   JPEG File(*.jpg)");
    if (filepath_certificate == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_certificate);
        ui->label_certificateFilePath->setText(filepath_certificate);
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
        ui->label_driverLicenseFilePath->setText(filepath_driversLicense);
        //int sendInt = send(int socket, filepath_driversLicense, size_t len, int flag);
    }
}


void requestVerification::on_pushButton_submitVerificationRequest_clicked()
{
    if (ui->lineEdit_linkedInLine->text().length() < 3)
    {
        QMessageBox::warning(this, "Link too short", "<font size = 13>Your Linkedin link is too short.</font>");
    }
    else if (ui->lineEdit_linkedInLine->text().contains("linkedin.com"))
    {
        QMessageBox::warning(this, "Full URL not needed", "<font size = 13>Include only the part after linkedin.com/in/</font>");
    }
    else if (ui->comboBox_occupations->currentText() == "")
    {
        QMessageBox::critical(this, "No Occupation", "<font size =  13>No occupation was selected.</font>");
    }
    else if (ui->label_certificateFilePath->text().contains("No file selected") &&
             ui->label_resumeFilePath->text().contains("No file selected") &&
             ui->label_degreeFilePath->text().contains("No file selected") &&
             ui->label_driverLicenseFilePath->text().contains("No file selected"))
    {
        QMessageBox::critical(this, "No Files", "<font size =  13>No files were selected for submission.</font>");
    }
    else
    {
        // send Linkedin to client
        // *send to client* ui->lineEdit_LinkedInLine->text();
        //ui->lineEdit_LinkedInLine->setText("LFEAZEL");
        //ui->lineEdit_linkedInLine->setReadOnly(true);
        QMessageBox::information(this, "Request Received", "<font size = 13>Your verification request has been submitted.</font>");
        close();
    }
}


void requestVerification::on_pushButton_cancelVerificationRequest_clicked()
{
    close();
}

