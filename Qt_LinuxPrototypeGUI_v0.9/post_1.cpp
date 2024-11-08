#include "post_1.h"
#include "ui_post_1.h"
#include "answerwindow.h"
#include "makecommentorpost.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>

Post_1::Post_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Post_1)
{
    ui->setupUi(this);

    /*

    // Profile Mini Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    QString *filepath_profileMiniPicPostFromClient[size length];

    int receiveInt = recv(int socket, *filepath_profileMiniPicPostFromClient, size_t len, int flag);

    QPixmap pix4(filepath_profileMiniPicPostFromClient);
    ui->label_userPic->setPixmap(pix4.scaled(100,100,Qt::KeepAspectRatio));


    // Upvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_upvotePostPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_upvotePostPicFromClient, size_t len, int flag);

    QPixmap pix6(filepath_upvotePostPicFromClient);
    QIcon (ButtonIcon(pix6);
    ui->pushButton_upPost->setIcon(ButtonIcon);
    ui->pushButton_upPost->setIconSize(QSize(40,40));


    // Upvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *upvotePostCountFromClient;

    int receiveInt = recv(int socket, *upvotePostCountFromClient, size_t len, int flag);

    QString upvotePostCountFromClientStr = QString::number(upvotePostCountFromClient);

    ui->label_upPostCount->setText(upvotePostCountFromClientStr);


    // Downvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *downvotePostCountFromClient;

    int receiveInt = recv(int socket, *upvotePostCountFromClient, size_t len, int flag);

    QString downvotePostCountFromClientStr = QString::number(downvotePostCountFromClient);

    ui->label_upPostCount->setText(downvotePostCountFromClientStr);


    // Downvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_downvotePostPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_downvotePostPicFromClient, size_t len, int flag);

    QPixmap pix7(filepath_downvotePostPicFromClient);
    QIcon (ButtonIcon_2(pix7);
    ui->pushButton_downPost->setIcon(ButtonIcon_2);
    ui->pushButton_downPost->setIconSize(QSize(40,40));

    */

    QPixmap pix4("/home/vboxuser/Pictures/profilePic.jpg");
    ui->label_userPic->setPixmap(pix4.scaled(100,100,Qt::KeepAspectRatio));

    QPixmap pix6("/home/vboxuser/Pictures/upvote.png");
    QIcon ButtonIcon(pix6);
    ui->pushButton_upPost->setIcon(ButtonIcon);
    ui->pushButton_upPost->setIconSize(QSize(40,40));

    QPixmap pix7("/home/vboxuser/Pictures/downvote.png");
    QIcon ButtonIcon_2(pix7);
    ui->pushButton_downPost->setIcon(ButtonIcon_2);
    ui->pushButton_downPost->setIconSize(QSize(40,40));

    ui->plainTextEdit_questionText->setReadOnly(true);

    //if already upvoted/downvoted
    //ui->pushButton_upPost->hide();
    //ui->pushButton_downPost->hide();


    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget);
    //ui->listWidget->addItem(item);

    /*

    // Answers List

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *postsAnswersListFromClient[number of items];

    int receiveInt = recv(int socket, *postsAnswersListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addPostsAnswersToList = postsAnswersListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addPostsAnswersToList, ui->listWidget);
        ui->listWidget->addItem(item);
    }

    // Post/Question Content

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *questionContentFromClient;

    int receiveInt = recv(int socket, *questionContentFromClient, size_t len, int flag);

    ui->textEdit_postQ->setPlainText(questionContentFromClient);

    */
}

Post_1::~Post_1()
{
    delete ui;
}

//To add from lineEdit. Text may need to be QString.
//QListWidgetItem *item = new QListWidgetItem(ui->line_edit->text(), ui->listWidget);

//QListWidgetItem(text to add, which list to add to);

// Example:
//QListWidgetItem("Who is The Rock?", ui->listWidget_communitiesTab);

//ui->listWidget->addItem(item);

//ui->line_edit->clear();
//ui->line_edit->setFocus();

void Post_1::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    answerWindow answerWindow_1;
    answerWindow_1.showMaximized();
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    answerWindow_1.exec();
}


void Post_1::on_pushButton_clicked()
{
    // if (verified)
    //{
    makeCommentOrPost makeCommentOrPost_1;
    makeCommentOrPost_1.showMaximized();
    makeCommentOrPost_1.exec();
    //}
    // else // (not verified)
    //{
    //  QMessageBox::critical(this, "Answer option not availlable to you", "You must be a verified user to post an answer.");
    //}
}


void Post_1::on_pushButton_upPost_clicked()
{
    int postUpvotesInt = ui->label_upPostCount->text().toInt();
    postUpvotesInt = postUpvotesInt + 1;
    QString postUpvotesStr = QString::number(postUpvotesInt);
    ui->label_upPostCount->setText(postUpvotesStr);
    ui->pushButton_upPost->hide();
    ui->pushButton_downPost->hide();
}


void Post_1::on_pushButton_downPost_clicked()
{
    int postDownvotesInt = ui->label_downPostCount->text().toInt();
    postDownvotesInt = postDownvotesInt + 1;
    QString postDownvotesStr = QString::number(postDownvotesInt);
    ui->label_downPostCount->setText(postDownvotesStr);
    ui->pushButton_downPost->hide();
    ui->pushButton_upPost->hide();
}

void Post_1::on_pushButton_2_clicked()
{
    QMessageBox::critical(this, "Question File", "<font size = 13>No file was submitted</font>");
    ui->pushButton_2->hide();
    /*

    if (no file)
    {
        QMessageBox::critical(this, "Question File", "<font size = 13>No file was submitted</font>");
        ui->pushButton_2->hide();
    }
    else
    {
        int sendInt = send(int socket, void *data, size_t len, int flag);

        QString *filepath_certificateFromClient[number];

        int receiveInt = recv(int socket, *filepath_certificateFromClient, size_t len, int flag);

        QDesktopServices::openUrl(QUrl::fromLocalFile(filepath_certificateFromClient));
    }

    */
}

