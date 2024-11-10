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

    ui->pushButton_profilePic->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_changeIcon->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_AddCertificates->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_AddDegree->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_AddDriverLicense->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_AddResume->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ViewCertificates->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ViewDegree->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ViewResume->setFocusPolicy(Qt::NoFocus);


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

    QString filepath_profPic = "/home/vboxuser/Pictures/profilePic.jpg";
    QPixmap pix3(filepath_profPic);
    QIcon ButtonIcon(pix3);
    ui->pushButton_profilePic->setIcon(ButtonIcon);
    ui->pushButton_profilePic->setIconSize(QSize(700,700));
    //ui->pushButton_profilePic->setPixmap(pix3.scaled(700,700,Qt::KeepAspectRatio)); //for labels onlyy
    ui->label_savedPath->setText(filepath_profPic);

    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes


    // Posts List

    int *postsProfileListFromClient[number of items];

    int receiveInt = recv(int socket, *postsProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addPostsProfileToList = postsProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addPostsProfileToList, ui->listWidget_postsFromProfile);
        ui->listWidget_postsFromProfile->addItem(item);
    }


    // Comments List

    sendInt = send(int socket, void *data, size_t len, int flag);

    int *commentsProfileListFromClient[number of items];

    receiveInt = recv(int socket, *commentsProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addCommentsProfileToList = commentsProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addCommentsProfileToList, ui->listWidget_commentsFromProfile);
        ui->listWidget_commentsFromProfile->addItem(item);
    }


    // Answers List

    sendInt = send(int socket, void *data, size_t len, int flag);

    int *answersProfileListFromClient[number of items];

    receiveInt = recv(int socket, *answersProfileListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addAnswersProfileToList = answersProfileListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addAnswersProfileToList, ui->listWidget_answersFromProfile);
        ui->listWidget_answersFromProfile->addItem(item);
    }

    if (not verfied)
    {
        QListWidgetItem *item = new QListWidgetItem("Not a verified user", ui->listWidget_answersFromProfile);
        item->setFlag(item->flags() & ~Qt::ItemIsSelectable);
        ui->listWidget_answersFromProfile->addItem(item);
    }

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
    post_3.showMaximized();
    post_3.exec();
}


void Profile::on_listWidget_commentsFromProfile_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    comment_1 comment_3;
    comment_3.showMaximized();
    comment_3.exec();
}


void Profile::on_listWidget_answersFromProfile_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    answerWindow answerWindow_3;
    answerWindow_3.showMaximized();
    answerWindow_3.exec();
}


void Profile::on_lineEdit_LinkedInLine_returnPressed()
{
    if (ui->lineEdit_LinkedInLine->text().length() < 3)
    {
        QMessageBox::warning(this, "Link too short", "<font size = 13>Your Linkedin link is too short.</font>");
    }
    else if (ui->lineEdit_LinkedInLine->text().contains("linkedin.com"))
    {
        QMessageBox::warning(this, "Full URL not needed", "<font size = 13>Include only the part after linkedin.com/in/</font>");
    }
    else
    {
        // send Linkedin to client
        // *send to client* ui->lineEdit_LinkedInLine->text();
        //ui->lineEdit_LinkedInLine->setText("LFEAZEL");
        ui->lineEdit_LinkedInLine->setReadOnly(true);
    }
}


void Profile::on_pushButton_changeIcon_clicked()
{
    QString filepath_profilePic=QFileDialog::getOpenFileName(this, tr("Open file"), "C://", "JPG File(*.jpg);; PNG File(*.png)");
    if (filepath_profilePic == "")
    {
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        //QPixmap pix33"/home/vboxuser/Pictures/otherPic.jpg");
        QPixmap pix33(filepath_profilePic);
        QIcon ButtonIcon(pix33);
        ui->pushButton_profilePic->setIcon(ButtonIcon);
        ui->pushButton_profilePic->setIconSize(QSize(700,700));
        ui->label_savedPath->setText(filepath_profilePic);

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
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
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
        QMessageBox::information(this, "Received File", "<font size = 13>No file selected.</font>");
    } else {
        QMessageBox::information(this, "Received File", filepath_degree);
        //int sendInt = send(int socket, filepath_degree, size_t len, int flag);
    }
}


void Profile::on_pushButton_AddCertificates_clicked()
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


void Profile::on_pushButton_AddDriverLicense_clicked()
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


void Profile::on_pushButton_profilePic_clicked()
{

    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_profilePicoid *datFromClient[number];

    int receiveInt = recv(int socket, *filepath_profilePicFromClient, size_t len, int flag);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_profilePicFromClient));

    */

    QString fileName = ui->label_savedPath->text();
    //QString fileName = "/home/vboxuser/Pictures/otherPic.jpg";
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void Profile::on_pushButton_ViewResume_clicked()
{
    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_resumeFromClient[number];

    int receiveInt = recv(int socket, *filepath_resumeFromClient, size_t len, int flag);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_resumeFromClient));

    */
}


void Profile::on_pushButton_ViewDegree_clicked()
{
    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_degreeFromClient[number];

    int receiveInt = recv(int socket, *filepath_degreeFromClient, size_t len, int flag);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_degreeFromClient));

    */
}


void Profile::on_pushButton_ViewCertificates_clicked()
{
    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_certificateFromClient[number];

    int receiveInt = recv(int socket, *filepath_certificateFromClient, size_t len, int flag);

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_certificateFromClient));

    */
}

