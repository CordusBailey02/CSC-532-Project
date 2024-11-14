#include "makequestion.h"
#include "ui_makequestion.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <arpa/inet.h>
extern "C" {
#include "terrorexchangegui.h"
}

makeQuestion::makeQuestion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::makeQuestion)
{
    ui->setupUi(this);

    ui->pushButton_uploadQuestionImage->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_postQuestion->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_cancel->setFocusPolicy(Qt::NoFocus);

    printf("The current user is: %s.\n", current_username);

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

    std::string question_str = postText.toStdString();
    char* question_c_str = new char[question_str.size() + 1];
    strcpy(question_c_str, question_str.c_str());

    // Send postText to client to display in question
    char input_buffer[4096];
    sprintf(input_buffer, "SEND POST_CREATE %s %d %s", current_username, 0, question_c_str);

    send(client_tcp_socket, &input_buffer, sizeof(input_buffer), 0);
}


void makeQuestion::on_pushButton_uploadQuestionImage_clicked()
{
    QString filepath_questionPic=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_questionPic == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        //QMessageBox::information(this, "Received File", filepath_questionPic);
        QPixmap pix4(filepath_questionPic);
        ui->label_questionFileSelected->setPixmap(pix4.scaled(200,200,Qt::KeepAspectRatio));
        //ui->label_questionFileSelected->setText(filepath_questionPic);
        //int sendInt = send(int socket, filepath_profilePic, size_t len, int flag);
    }
}

