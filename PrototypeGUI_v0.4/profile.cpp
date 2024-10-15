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

    QPixmap pix3("C:/Users/ldura/Pictures/Bacc Pics/ae.jpg");
    QIcon ButtonIcon(pix3);
    ui->pushButton_profilePic->setIcon(ButtonIcon);
    ui->pushButton_profilePic->setIconSize(QSize(150,150));
    //ui->pushButton_profilePic->setPixmap(pix3.scaled(100,100,Qt::KeepAspectRatio));
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
    // send Linkedin to client
    // *send to client* ui->lineEdit_LinkedInLine->text();
    ui->lineEdit_LinkedInLine->setReadOnly(true);
}

