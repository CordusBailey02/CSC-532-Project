#include "searchresults.h"
#include "ui_searchresults.h"

searchResults::searchResults(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchResults)
{
    ui->setupUi(this);
}

searchResults::~searchResults()
{
    delete ui;
}

void searchResults::on_listWidget_communitiesFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    communitiesTab_4 = new communitiesTab(this);
    communitiesTab_4->show();
}


void searchResults::on_listWidget_postsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    post_4 = new Post_1(this);
    post_4->show();
}


void searchResults::on_listWidget_commentsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    comment_4 = new comment_1(this);
    comment_4->show();
}

