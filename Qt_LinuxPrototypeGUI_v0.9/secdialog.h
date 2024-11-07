#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_profileButton_clicked();

    void on_listWidget_defaultList_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_favoriteList_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_askAQuestion_clicked();

    void on_listWidget_communitiesList_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_searchButton_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
