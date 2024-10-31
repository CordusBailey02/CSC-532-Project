#include "secdialog.h"
#include "ui_secdialog.h"
#include "post_1.h"
#include "communitiestab.h"
#include "makequestion.h"
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
    ui->pushButton_profileButton->setIcon(ButtonIcon);
    ui->pushButton_profileButton->setIconSize(QSize(50,50));
    //ui->pushButton_profileButton->setPixmap(pix2.scaled(100,100,Qt::KeepAspectRatio));

    /*
    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    QString *communitiesListFromClient[number of items];

    int receiveInt = recv(int socket, *communitiesListFromClient, size_t len, int flag);

    Different send/recv for each list in the Window?

    for (int i = 0; i < number of items; i++)
    {
        QString addCommunityToList = communitiesListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addCommunityToList, ui->listWidget_communitiesList);
        ui->listWidget_communitiesList->addItem(item);
    }


    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *favoriteListFromClient[number of items];

    int receiveInt = recv(int socket, *favoriteListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addFavoriteToList = favoriteListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addFavoriteToList, ui->listWidget_favoriteList);
        ui->listWidget_favoriteList->addItem(item);
    }


    int sendInt = send(int socket, void *data, size_t len, int flag);

    QString *defaultListFromClient[number of items];

    int receiveInt = recv(int socket, *defaultListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addDefaultToList = defaultListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addDefaultToList, ui->listWidget_defaultList);
        ui->listWidget_defaultList->addItem(item);
    }


    QListWidgetItem *item = new QListWidgetItem(ui->line_edit->text(), ui->listWidget);

    QListWidgetItem(text to add, which list to add to);

    Example:
    QListWidgetItem("Who is The Rock?", ui->listWidget_communitiesTab);

    ui->listWidget->addItem(item);

    */
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_profileButton_clicked()
{
    // Profile clicked
    Profile profile_1;
    profile_1.exec();
}


void SecDialog::on_listWidget_defaultList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    //QListWidgetItem *selectedItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    // give selectedItem to post
    //QMessageBox::information(this, "Double Clicked", "Again: " + selectedItem->text());
    Post_1 post;
    post.exec();
}


void SecDialog::on_listWidget_favoriteList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    Post_1 post;
    post.exec();
}


void SecDialog::on_pushButton_askAQuestion_clicked()
{
    makeQuestion makeQuestion_1;
    makeQuestion_1.exec();
}


void SecDialog::on_listWidget_communitiesList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab communitiesTab_1;
    communitiesTab_1.exec();
}


void SecDialog::on_pushButton_searchButton_clicked()
{
    searchResults searchResults_1;
    searchResults_1.exec();
}
