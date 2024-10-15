#include "secdialog.h"
#include "ui_secdialog.h"
#include "post_1.h"
#include "communitiestab.h"
#include "makecommentorpost.h"
#include "searchresults.h"
#include "profile.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>

SecDialog::SecDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QPixmap pix2("C:/Users/ldura/Pictures/Bacc Pics/ae.jpg");
    QIcon ButtonIcon(pix2);
    ui->pushButton_2->setIcon(ButtonIcon);
    ui->pushButton_2->setIconSize(QSize(50,50));
    //ui->pushButton_2->setPixmap(pix2.scaled(100,100,Qt::KeepAspectRatio));

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_2_clicked()
{
    Profile profile_1;
    profile_1.exec();
}


void SecDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    //QListWidgetItem *selectedItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    // give selectedItem to post
    //QMessageBox::information(this, "Double Clicked", "Again: " + selectedItem->text());
    Post_1 post;
    post.exec();
}


void SecDialog::on_listWidget_3_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    Post_1 post;
    post.exec();
}


void SecDialog::on_pushButton_clicked()
{
    makeCommentOrPost makeCommentOrPost_1;
    makeCommentOrPost_1.exec();
}


void SecDialog::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab communitiesTab_1;
    communitiesTab_1.exec();
}


void SecDialog::on_pushButton_3_clicked()
{
    searchResults searchResults_1;
    searchResults_1.exec();
}

