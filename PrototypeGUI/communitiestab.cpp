#include "communitiestab.h"
#include "ui_communitiestab.h"

communitiesTab::communitiesTab(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::communitiesTab)
{
    ui->setupUi(this);
}

communitiesTab::~communitiesTab()
{
    delete ui;
}

void communitiesTab::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    post_2 = new Post_1(this);
    item->text();
    post_2->show();
}

