#include "makequestion.h"
#include "ui_makequestion.h"
#include <QtWidgets>

makeQuestion::makeQuestion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::makeQuestion)
{
    ui->setupUi(this);

    /*

    */
}

makeQuestion::~makeQuestion()
{
    delete ui;
}

void makeQuestion::on_pushButton_cancel_clicked()
{
    close();
}


void makeQuestion::on_pushButton_postQuestion_clicked()
{
    QString postText = ui->plainTextEdit->toPlainText();
    postText = postText.toLower();
    // Send postText to client to display in question
}


void makeQuestion::on_pushButton_uploadQuestionImage_clicked()
{
    QString filepath_questionPic=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_questionPic == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_questionPic);
        ui->label_questionFileSelected->setText(filepath_questionPic);
        //int sendInt = send(int socket, filepath_profilePic, size_t len, int flag);
    }
}

