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

    ui->textEdit_AnswerQ->setReadOnly(true);

    QPixmap pix5("C:/Users/ldura/Pictures/Mesa/me_3_closer.jpg");
    ui->label_answerPic->setPixmap(pix5.scaled(100,100,Qt::KeepAspectRatio));

    QPixmap pix8("C:/Users/ldura/Pictures/upvote.jpg");
    QIcon ButtonIcon(pix8);
    ui->pushButton_upAnswer->setIcon(ButtonIcon);
    ui->pushButton_upAnswer->setIconSize(QSize(40,40));

    QPixmap pix9("C:/Users/ldura/Pictures/downvote.jpg");
    QIcon ButtonIcon_2(pix9);
    ui->pushButton_downAnswer->setIcon(ButtonIcon_2);
    ui->pushButton_downAnswer->setIconSize(QSize(40,40));

}

answerWindow::~answerWindow()
{
    delete ui;
}

void answerWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    comment_1 comment_5;
    item->text();
    comment_5.exec();
}


void answerWindow::on_pushButton_commentBtn_clicked()
{
    makeCommentOrPost makeCommentOrPost_5;
    makeCommentOrPost_5.exec();
}

