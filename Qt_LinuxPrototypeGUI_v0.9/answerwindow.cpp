#include "answerwindow.h"
#include "ui_answerwindow.h"
#include "comment_1.h"
#include "makecommentorpost.h"
#include <QPixmap>
#include <QIcon>

answerWindow::answerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::answerWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit_answerText->setReadOnly(true);

    QPixmap pix5("C:/Users/ldura/Pictures/Mesa/me_3_closer.jpg");
    ui->label_answerPic->setPixmap(pix5.scaled(100,100,Qt::KeepAspectRatio));

    QPixmap pix10("C:/Users/ldura/Pictures/upvote.jpg");
    QIcon ButtonIcon(pix10);
    ui->pushButton_upAnswer->setIcon(ButtonIcon);
    ui->pushButton_upAnswer->setIconSize(QSize(40,40));

    QPixmap pix11("C:/Users/ldura/Pictures/downvote.jpg");
    QIcon ButtonIcon_2(pix11);
    ui->pushButton_downAnswer->setIcon(ButtonIcon_2);
    ui->pushButton_downAnswer->setIconSize(QSize(40,40));

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget);
    //ui->listWidget->addItem(item);

    /*

    // Profile Mini Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    QString *filepath_profileMiniPicAnswerFromClient[size length];

    int receiveInt = recv(int socket, *filepath_profileMiniPicAnswerFromClient, size_t len, int flag);

    QPixmap pix5(filepath_profileMiniPicAnswerFromClient);
    ui->label_answerPic->setPixmap(pix5.scaled(60,60,Qt::KeepAspectRatio));


    // Upvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_upvoteAnswerPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_upvoteAnswerPicFromClient, size_t len, int flag);

    QPixmap pix10(filepath_upvoteAnswerPicFromClient);
    QIcon (ButtonIcon(pix10);
    ui->pushButton_upAnswer->setIcon(ButtonIcon);
    ui->pushButton_upAnswer->setIconSize(QSize(40,40));


    // Upvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *upvoteAnswerCountFromClient;

    int receiveInt = recv(int socket, *upvoteAnswerCountFromClient, size_t len, int flag);

    QString upvoteAnswerCountFromClientStr = QString::number(upvoteAnswerCountFromClient);

    ui->label_upAnswerCount->setText(upvoteAnswerCountFromClientStr);


    // Downvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *downvoteAnswerCountFromClient;

    int receiveInt = recv(int socket, *upvoteAnswerCountFromClient, size_t len, int flag);

    QString downvoteAnswerCountFromClientStr = QString::number(downvoteAnswerCountFromClient);

    ui->label_downAnswerCount->setText(downvoteAnswerCountFromClientStr);


    // Downvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_downvoteAnswerPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_downvoteAnswerPicFromClient, size_t len, int flag);

    QPixmap pix11(filepath_downvoteAnswerPicFromClient);
    QIcon ButtonIcon_2(pix11);
    ui->pushButton_downAnswer->setIcon(ButtonIcon_2);
    ui->pushButton_downAnswer->setIconSize(QSize(40,40));


    // Answer Content

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *answerContentFromClient;

    int receiveInt = recv(int socket, *answerContentFromClient, size_t len, int flag);

    ui->textEdit_AnswerQ->setPlainText(answerContentFromClient);


    // Comments List

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *postsCommentsListFromClient[number of items];

    int receiveInt = recv(int socket, *postsCommentsListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addPostsCommentsToList = postsCommentsListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addPostsCommentsToList, ui->listWidget);
        ui->listWidget->addItem(item);
    }

    */

}

answerWindow::~answerWindow()
{
    delete ui;
}

void answerWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    comment_1 comment_5;
    comment_5.showMaximized();
    item->text();
    comment_5.exec();
}


void answerWindow::on_pushButton_commentBtn_clicked()
{
    makeCommentOrPost makeCommentOrPost_5;
    makeCommentOrPost_5.showMaximized();
    makeCommentOrPost_5.exec();
}


void answerWindow::on_pushButton_upAnswer_clicked()
{
    int answerUpvotesInt = ui->label_upAnswerCount->text().toInt();
    answerUpvotesInt = answerUpvotesInt + 1;
    QString answerUpvotesStr = QString::number(answerUpvotesInt);
    ui->label_upAnswerCount->setText(answerUpvotesStr);
    ui->pushButton_upAnswer->hide();

    // send new value to client
}


void answerWindow::on_pushButton_downAnswer_clicked()
{
    int answerDownvotesInt = ui->label_downAnswerCount->text().toInt();
    answerDownvotesInt = answerDownvotesInt + 1;
    QString answerDownvotesStr = QString::number(answerDownvotesInt);
    ui->label_downAnswerCount->setText(answerDownvotesStr);
    ui->pushButton_downAnswer->hide();

    // send new value to client
}
