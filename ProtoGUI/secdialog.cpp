#include "secdialog.h"
#include "ui_secdialog.h"
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

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

    QSqlDatabase db = QSqlDatabase::addDatabase("SQLITE");
    db.setDatabaseName("C:/Users/ldura/mydatabase.db");
    if (!db.open())
    {
        QMessageBox::critical(nullptr, "Error", db.lastError().text());
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS numbers (id INTEGER PRIMARY KEY, number INTEGER)")) {
        QMessageBox::critical(nullptr, "Error", query.lastError().text());
    }

    for (int i = 1; i <= 5; ++i) {
        query.prepare("INSERT INTO numbers (number) VALUES (?)");
        query.addBindValue(i);
        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Error", query.lastError().text());
        }
    }

    query.exec("SELECT number FROM numbers");
    while (query.next()) {
        ui->listWidget->addItem(query.value(0).toString());
    }

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_2_clicked()
{
    profile = new Profile(this);
    profile->show();
}


void SecDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    post = new Post_1(this);
    QMessageBox::information(this, "Double Clicked", "You double clicked on: " + item->text());
    post->show();
}

