#include "searchresults.h"
#include "ui_searchresults.h"
#include "answerwindow.h"
#include "post_1.h"
#include "comment_1.h"
#include "communitiestab.h"

searchResults::searchResults(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchResults)
{
    ui->setupUi(this);

    ui->label_searchPrompt->setText("No prompt given");

    /*

    int sendInt = send(int socket, void *data, size_t len, int flag);
    -1 -> something wrong
    0  -> no bytes received
    n  -> received n bytes

    QString *communitiesSearchListFromClient[number of items];

    int receiveInt = recv(int socket, *communitiesSearchListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addCommunitySearchToList = communitiesSearchListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addCommunitySearchToList, ui->listWidget_communitiesFromSearch);
        ui->listWidget_communitiesFromSearch->addItem(item);
    }


    sendInt = send(int socket, void *data, size_t len, int flag);

    QString *postsSearchListFromClient[number of items];

    receiveInt = recv(int socket, *postsSearchListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addPostsSearchToList = postsSearchListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addPostsSearchToList, ui->listWidget_postsFromSearch);
        ui->listWidget_postsFromSearch->addItem(item);
    }


    sendInt = send(int socket, void *data, size_t len, int flag);

    QString *commentsSearchListFromClient[number of items];

    receiveInt = recv(int socket, *commentsSearchListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addCommentsSearchToList = commentsSearchListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addCommentsSearchToList, ui->listWidget_commentsFromSearch);
        ui->listWidget_commentsFromSearch->addItem(item);
    }


    sendInt = send(int socket, void *data, size_t len, int flag);

    QString *answersSearchListFromClient[number of items];

    receiveInt = recv(int socket, *answersSearchListFromClient, size_t len, int flag);

    for (int i = 0; i < number of items; i++)
    {
        QString addAnswersSearchToList = answersSearchListFromClient[i];
        QListWidgetItem *item = new QListWidgetItem(addAnswersSearchToList, ui->listWidget_answersFromSearch);
        ui->listWidget_answersFromSearch->addItem(item);
    }


    */

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget_communitiesFromSearch);
    //ui->listWidget_communitiesFromSearch->addItem(item);

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget_postsFromSearch);
    //ui->listWidget_postsFromSearch->addItem(item);

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget_commentsFromSearch);
    //ui->listWidget_commentsFromSearch->addItem(item);

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget_answersFromSearch);
    //ui->listWidget_answersFromSearch->addItem(item);
}

searchResults::~searchResults()
{
    delete ui;
}

void searchResults::on_listWidget_communitiesFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab communitiesTab_4;
    communitiesTab_4.showMaximized();
    communitiesTab_4.exec();
}


void searchResults::on_listWidget_postsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    Post_1 post_4;
    post_4.showMaximized();
    post_4.exec();
}


void searchResults::on_listWidget_commentsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    comment_1 comment_4;
    comment_4.showMaximized();
    comment_4.exec();
}


void searchResults::on_listWidget_answersFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    answerWindow answerWindow_1;
    answerWindow_1.exec();
}

