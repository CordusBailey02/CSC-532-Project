#include "post_1.h"
#include "ui_post_1.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>

Post_1::Post_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Post_1)
{
    ui->setupUi(this);

    QPixmap pix4("C:/Users/ldura/Pictures/Bacc Pics/ae.jpg");
    ui->label_userPic->setPixmap(pix4.scaled(60,60,Qt::KeepAspectRatio));

    QPixmap pix6("C:/Users/ldura/Pictures/upvote.jpg");
    QIcon ButtonIcon(pix6);
    ui->pushButton_upPost->setIcon(ButtonIcon);
    ui->pushButton_upPost->setIconSize(QSize(40,40));

    QPixmap pix7("C:/Users/ldura/Pictures/downvote.jpg");
    QIcon ButtonIcon_2(pix7);
    ui->pushButton_downPost->setIcon(ButtonIcon_2);
    ui->pushButton_downPost->setIconSize(QSize(40,40));

    ui->textEdit_postQ->setReadOnly(true);
}

Post_1::~Post_1()
{
    delete ui;
}

//QListWidgetItem *item = new QListWidgetItem(ui->line_edit->text(), ui->listWidget);
//ui->listWidget->addItem(item);
//ui->line_edit->clear();
//ui->line_edit->setFocus();

void Post_1::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    comment = new comment_1(this);
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    comment->show();
}


void Post_1::on_pushButton_clicked()
{
    makeCommentOrPost_1 = new makeCommentOrPost(this);
    makeCommentOrPost_1->show();
}

