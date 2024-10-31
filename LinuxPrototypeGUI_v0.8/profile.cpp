#include "profile.h"
#include "ui_profile.h"
#include "comment_1.h"
#include "post_1.h"
#include "answerwindow.h"
#include <QPixmap>
#include <QIcon>

Profile::Profile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);

    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_profilePicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_profilePicFromClient, size_t len, int flag);

    QPixmap pix3(filepath_profilePicFromClient);
    QIcon (ButtonIcon(pix3);
    ui->pushButton_profilePic->setIcon(ButtonIcon);
    ui->pushButton_profilePic->setIconSize(QSize(150,150));


    sendInt = send(int socket, void *data, size_t len, int flag);

    QString *linkedIn_fromClient[size length];

    receiveInt = recv(int socket, *linkedIn_fromClient, size_t len, int flag);

    if (linkedIn_fromClient == "")
    {
        ui->lineEdit_LinkedInLine->clear();
        ui->lineEdit_LinkedInLine->setReadOnly(false);
    } else
    {
        ui->lineEdit_LinkedInLine->setText(linkedIn_fromClient);
        ui->lineEdit_LinkedInLine->setReadOnly(true);
    }

    */

    QPixmap pix3("C:/Users/ldura/Pictures/Bacc Pics/ae.jpg");
    QIcon ButtonIcon(pix3);
    ui->pushButton_profilePic->setIcon(ButtonIcon);
    ui->pushButton_profilePic->setIconSize(QSize(150,150));
    //ui->pushButton_profilePic->setPixmap(pix3.scaled(100,100,Qt::KeepAspectRatio));

    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    int *postsProfileListFromClient[number of items];

    int receiveInt = recv(int socket, *postsProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addPostsProfileToList = postsProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addPostsProfileToList, ui->listWidget_postsFromProfile);
        ui->listWidget_postsFromProfile->addItem(item);
    }

    sendInt = send(int socket, void *data, size_t len, int flag);

    int *commentsProfileListFromClient[number of items];

    receiveInt = recv(int socket, *commentsProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addCommentsProfileToList = commentsProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addCommentsProfileToList, ui->listWidget_commentsFromProfile);
        ui->listWidget_commentsFromProfile->addItem(item);
    }


    sendInt = send(int socket, void *data, size_t len, int flag);

    int *answersProfileListFromClient[number of items];

    receiveInt = recv(int socket, *answersProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addAnswersProfileToList = answersProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addAnswersProfileToList, ui->listWidget_answersFromProfile);
        ui->listWidget_answersFromProfile->addItem(item);
    }


     *
     *
    */
}

Profile::~Profile()
{
    delete ui;
}

void Profile::on_listWidget_postsFromProfile_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    Post_1 post_3;
    post_3.exec();
}


void Profile::on_listWidget_commentsFromProfile_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    comment_1 comment_3;
    comment_3.exec();
}


void Profile::on_listWidget_answersFromProfile_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    answerWindow answerWindow_3;
    answerWindow_3.exec();
}


void Profile::on_lineEdit_LinkedInLine_returnPressed()
{
    if (ui->lineEdit_LinkedInLine->text().length() < 3)
    {
        QMessageBox::warning(this, "Link too short", "Your Linkedin link is too short. Include only the part after linkedin.com/in/");
    }
    else if (ui->lineEdit_LinkedInLine->text().contains("linkedin.com"))
    {
        QMessageBox::warning(this, "Full URL not needed", "Include only the part after linkedin.com/in/");
    }
    else
    {
        // send Linkedin to client
        // *send to client* ui->lineEdit_LinkedInLine->text();
        //ui->lineEdit_LinkedInLine->setText("LFEAZEL");
        ui->lineEdit_LinkedInLine->setReadOnly(true);
    }
}


void Profile::on_pushButton_clicked()
{
    QString filepath_profilePic=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_profilePic == "")
    {
        QMessageBox::information(this, "Received File", "No file selected.");
    } else {
        QMessageBox::information(this, "Received File", filepath_profilePic);
        //int sendInt = send(int socket, filepath_profilePic, size_t len, int flag);
    }
    // Will be C:/users/blah blah blah
}


void Profile::on_pushButton_AddResume_clicked()
{
    QString filepath_resume=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf)");
    if (filepath_resume == "")
    {
        QMessageBox::information(this, "Received File", "No file selected.");
    } else {
        QMessageBox::information(this, "Received File", filepath_resume);
        //int sendInt = send(int socket, filepath_resume, size_t len, int flag);
    }
}


void Profile::on_pushButton_AddDegree_clicked()
{
    QString filepath_degree=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_degree == "")
    {
        QMessageBox::information(this, "Received File", "No file selected.");
    } else {
        QMessageBox::information(this, "Received File", filepath_degree);
        //int sendInt = send(int socket, filepath_degree, size_t len, int flag);
    }
}


void Profile::on_pushButton_AddCertificates_clicked()
{
    QString filepath_certificates=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_certificates == "")
    {
        QMessageBox::information(this, "Received File", "No file selected.");
    } else {
        QMessageBox::information(this, "Received File", filepath_certificates);
        //int sendInt = send(int socket, filepath_certificates, size_t len, int flag);
    }
}


void Profile::on_pushButton_AddDriverLicense_clicked()
{
    QString filepath_driversLicense=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "PDF File(*.pdf);; JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_driversLicense == "")
    {
        QMessageBox::information(this, "Received File", "No file selected.");
    } else {
        QMessageBox::information(this, "Received File", filepath_driversLicense);
        //int sendInt = send(int socket, filepath_driversLicense, size_t len, int flag);
    }
}


void Profile::on_pushButton_profilePic_clicked()
{

    /*

    int sendInt = send(int socket, filepath_profilePic, size_t len, int flag);

    QString *filepath_profilePicFromClient[number];

    int receiveInt = recv(int socket, *filepath_profilePicFromClient, size_t len, int flag);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_profilePicFromClient));

    */

    QString fileName = "C:/Users/ldura/Pictures/Bacc Pics/ae.jpg";
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
