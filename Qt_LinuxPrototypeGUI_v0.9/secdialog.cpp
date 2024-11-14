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
#include <QDebug>
#include <arpa/inet.h>
extern "C" {
#include "terrorexchangegui.h"
}

SecDialog::SecDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    char input_buffer[4096];
    sprintf(input_buffer, "GET POST %d", 0);
    send(client_tcp_socket, &input_buffer, sizeof(input_buffer), 0);


    QPixmap pix2("/home/vboxuser/Pictures/profilePic.jpg");
    QIcon ButtonIcon(pix2);
    ui->pushButton_profileButton->setIcon(ButtonIcon);
    ui->pushButton_profileButton->setIconSize(QSize(200,200));
    //ui->pushButton_profileButton->setPixmap(pix2.scaled(100,100,Qt::KeepAspectRatio));

    ui->pushButton_askAQuestion->setFocusPolicy(Qt::NoFocus);


    ui->listWidget_defaultList->clear();

    char numOfPosts[1024];
    recv(client_tcp_socket, numOfPosts, sizeof(numOfPosts), 0);
    printf("Got num of posts: %d.\n", atoi(numOfPosts));

    char buffers[2024];
    recv(client_tcp_socket, buffers, sizeof(buffers), 0);

    // Convert char buffer to QString
    QString inputString = QString::fromUtf8(buffers);

    // Split the input into separate entries based on a newline delimiter
    QStringList entries = inputString.split("\n");  // Adjust delimiter if needed

    // Iterate through each entry
    for (const QString &entry : entries) {
        // Clean the input string by removing the square brackets and any unnecessary spaces
        QString cleanedInput = entry.trimmed().remove(0, 1).remove(entry.length() - 1, 1);

        // Split the string by the quotes and space delimiter
        QStringList parts = cleanedInput.split("\" \"");

        // Ensure there are enough parts to extract the necessary data
        if (parts.size() >= 5) {
            // Prepare the item with [] around "test" and the full question
            QString item = QString("[%1] %2").arg(parts[1].trimmed()).arg(parts[4].trimmed());

            // Add the item to the list widget
            ui->listWidget_defaultList->addItem(item);
        }
    }

    /*
    char buffers[2048];
    for(int i = 0; i < atoi(numOfPosts); i++)
    {
        memset(buffers, 0, sizeof(buffers));

        recv(client_tcp_socket, buffers, sizeof(buffers), 0);
        printf("Received post: %s.\n", buffers);

        // Convert char buffer to QString
        QString inputString = QString::fromUtf8(buffers);

        // Clean the input string by removing the square brackets
        QString cleanedInput = inputString.trimmed().remove(0, 1).remove(inputString.length() - 1, 1);

        // Split the string by the quotes and space delimiter
        QStringList parts = cleanedInput.split("\" \"");

        // Prepare the item with [] around "test" and the full question
        QString item = QString("[%1] %2").arg(parts[1].trimmed()).arg(parts[4].trimmed());

        // Add the item to the list widget
        ui->listWidget_defaultList->addItem(item);
    }
    */


    //QStringList items = {"Item 1", "Item 2", "Item 3", "Item 4"};
    //ui->listWidget_defaultList->addItems(items);

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
    //profile_1.show();
    profile_1.showMaximized();
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
    post.showMaximized();
    post.exec();
}


void SecDialog::on_listWidget_favoriteList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    //QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    Post_1 post;
    post.showMaximized();
    post.exec();
}


void SecDialog::on_pushButton_askAQuestion_clicked()
{
    makeQuestion makeQuestion_1;
    makeQuestion_1.showMaximized();
    makeQuestion_1.exec();
}


void SecDialog::on_listWidget_communitiesList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab communitiesTab_1;
    communitiesTab_1.showMaximized();
    communitiesTab_1.exec();
}


void SecDialog::on_pushButton_searchButton_clicked()
{
    if  (ui->lineEdit_searchBar->text() == "")
    {
        QMessageBox::critical(this, "Search Error", "<font size = 13>Search bar is empty.</font>");
    }
    else
    {
        searchResults searchResults_1;
        searchResults_1.showMaximized();
        searchResults_1.exec();
    }
}


void SecDialog::on_listWidget_faveCommunitiesList_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab communitiesTab_1;
    communitiesTab_1.showMaximized();
    communitiesTab_1.exec();
}

