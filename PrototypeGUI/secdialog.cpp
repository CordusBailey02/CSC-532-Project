#include "secdialog.h"
#include "ui_secdialog.h"
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
    profile = new Profile(this);
    if (!profile->isVisible())
    {
        profile->show();
        profile->raise();
    }
}


void SecDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    post = new Post_1(this);
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    //QListWidgetItem *selectedItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    // give selectedItem to post
    //QMessageBox::information(this, "Double Clicked", "Again: " + selectedItem->text());
    post->show();
}


void SecDialog::on_listWidget_3_itemDoubleClicked(QListWidgetItem *item)
{
    post = new Post_1(this);
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    post->show();
}


void SecDialog::on_pushButton_clicked()
{
    makeCommentOrPost_1 = new makeCommentOrPost(this);
    makeCommentOrPost_1->show();
}


void SecDialog::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    communitiesTab_1 = new communitiesTab(this);
    item->text();
    communitiesTab_1->show();
}


void SecDialog::on_pushButton_3_clicked()
{
    searchResults_1 = new searchResults(this);
    searchResults_1->show();
}

