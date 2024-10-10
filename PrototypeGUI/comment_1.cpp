#include "comment_1.h"
#include "ui_comment_1.h"
#include <QPixmap>
#include <QIcon>

comment_1::comment_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::comment_1)
{
    ui->setupUi(this);

    QPixmap pix5("C:/Users/ldura/Pictures/Mesa/me_3_closer.jpg");
    ui->label_commentUserPic->setPixmap(pix5.scaled(100,100,Qt::KeepAspectRatio));

    QPixmap pix8("C:/Users/ldura/Pictures/upvote.jpg");
    QIcon ButtonIcon(pix8);
    ui->pushButton_upComment->setIcon(ButtonIcon);
    ui->pushButton_upComment->setIconSize(QSize(40,40));

    QPixmap pix9("C:/Users/ldura/Pictures/downvote.jpg");
    QIcon ButtonIcon_2(pix9);
    ui->pushButton_downComment->setIcon(ButtonIcon_2);
    ui->pushButton_downComment->setIconSize(QSize(40,40));

    ui->textEdit_commentQ->setReadOnly(true);
}

comment_1::~comment_1()
{
    delete ui;
}
