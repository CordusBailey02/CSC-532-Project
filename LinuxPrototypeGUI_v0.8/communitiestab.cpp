#include "communitiestab.h"
#include "ui_communitiestab.h"
#include "post_1.h"

communitiesTab::communitiesTab(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::communitiesTab)
{
    ui->setupUi(this);

    //QListWidgetItem *item = new QListWidgetItem(QString text, ui->listWidget);
    //ui->listWidget->addItem(item);

    /*

    */
}

communitiesTab::~communitiesTab()
{
    delete ui;
}

void communitiesTab::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Post_1 post_2;
    item->text();
    post_2.exec();
}
