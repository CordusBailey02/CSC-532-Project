#include "comment_1.h"
#include "ui_comment_1.h"
#include <QPixmap>
#include <QIcon>

comment_1::comment_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::comment_1)
{
    ui->setupUi(this);

    QPixmap pix5("/home/vboxuser/Pictures/profilePic.jpg");
    ui->label_commentUserPic->setPixmap(pix5.scaled(300,300,Qt::KeepAspectRatio));

    QPixmap pix8("/home/vboxuser/Pictures/upvote.png");
    QIcon ButtonIcon(pix8);
    ui->pushButton_upComment->setIcon(ButtonIcon);
    ui->pushButton_upComment->setIconSize(QSize(40,40));

    QPixmap pix9("/home/vboxuser/Pictures/downvote.png");
    QIcon ButtonIcon_2(pix9);
    ui->pushButton_downComment->setIcon(ButtonIcon_2);
    ui->pushButton_downComment->setIconSize(QSize(40,40));

    ui->plainTextEdit_commentText->setReadOnly(true);

    ui->pushButton_upComment->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_downComment->setFocusPolicy(Qt::NoFocus);

    /*

    // Profile Mini Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    QString *filepath_profileMiniPicCommentFromClient[size length];

    int receiveInt = recv(int socket, *filepath_profileMiniPicCommentFromClient, size_t len, int flag);

    QPixmap pix4(filepath_profileMiniPicCommentFromClient);
    ui->label_commentUserPic->setPixmap(pix4.scaled(100,100,Qt::KeepAspectRatio));


    // Upvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_upvoteCommentPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_upvoteCommentPicFromClient, size_t len, int flag);

    QPixmap pix8(filepath_upvoteCommentPicFromClient);
    QIcon (ButtonIcon(pix8);
    ui->pushButton_upComment->setIcon(ButtonIcon);
    ui->pushButton_upComment->setIconSize(QSize(40,40));


    // Upvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *upvoteCommentCountFromClient;

    int receiveInt = recv(int socket, *upvoteCommentCountFromClient, size_t len, int flag);

    QString upvoteCommentCountFromClientStr = QString::number(upvoteCommentCountFromClient);

    ui->label_upCountComment->setText(upvoteCommentCountFromClientStr);


    // Downvote count

    int sendInt = send(int socket, void *data, size_t len, int flag);

    int *downvoteCommentCountFromClient;

    int receiveInt = recv(int socket, *upvoteCommentCountFromClient, size_t len, int flag);

    QString downvoteCommentCountFromClientStr = QString::number(downvoteCommentCountFromClient);

    ui->label_downCountComment->setText(downvoteCommentCountFromClientStr);


    // Downvote Picture

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *filepath_downvoteCommentPicFromClient[size length];

    int receiveInt = recv(int socket, *filepath_downvoteCommentPicFromClient, size_t len, int flag);

    QPixmap pix9(filepath_downvoteCommentPicFromClient);
    QIcon (ButtonIcon_2(pix9);
    ui->pushButton_downComment->setIcon(ButtonIcon_2);
    ui->pushButton_downComment->setIconSize(QSize(40,40));

    // Comment Content

    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *commentContentFromClient;

    int receiveInt = recv(int socket, *commentContentFromClient, size_t len, int flag);

    ui->textEdit_commentQ->setPlainText(commentContentFromClient);

    */
}

comment_1::~comment_1()
{
    delete ui;
}

void comment_1::on_pushButton_upComment_clicked()
{
    int commentUpvotesInt = ui->label_upCountComment->text().toInt();
    commentUpvotesInt = commentUpvotesInt + 1;
    QString commentUpvotesStr = QString::number(commentUpvotesInt);
    ui->label_upCountComment->setText(commentUpvotesStr);
    ui->pushButton_upComment->hide();
    ui->pushButton_downComment->hide();
}


void comment_1::on_pushButton_downComment_clicked()
{
    int commentDownvotesInt = ui->label_downCountComment->text().toInt();
    commentDownvotesInt = commentDownvotesInt + 1;
    QString commentDownvotesStr = QString::number(commentDownvotesInt);
    ui->label_downCountComment->setText(commentDownvotesStr);
    ui->pushButton_downComment->hide();
    ui->pushButton_upComment->hide();
}
