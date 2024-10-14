#include "searchresults.h"
#include "ui_searchresults.h"
#include "answerWindow.h"
#include "post_1.h"
#include "comment_1.h"
#include "communitiestab.h"

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
    communitiesTab communitiesTab_4;
    communitiesTab_4.exec();
}


void searchResults::on_listWidget_postsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    Post_1 post_4;
    post_4.exec();
}


void searchResults::on_listWidget_commentsFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    comment_1 comment_4;
    comment_4.exec();
}


void searchResults::on_listWidget_answersFromSearch_itemDoubleClicked(QListWidgetItem *item)
{
    item->text();
    answerWindow answerWindow_1;
    //answerWindow_1.setModal(false);
    answerWindow_1.exec();
}

