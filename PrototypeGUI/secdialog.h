#ifndef SECDIALOG_H
#define SECDIALOG_H

#include "profile.h"
#include "post_1.h"
#include "makecommentorpost.h"
#include "communitiestab.h"
#include "searchresults.h"
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
    void on_pushButton_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_3_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_3_clicked();

private:
    Ui::SecDialog *ui;
    Profile *profile;
    Post_1 *post;
    makeCommentOrPost *makeCommentOrPost_1;
    communitiesTab *communitiesTab_1;
    searchResults *searchResults_1;
};

#endif // SECDIALOG_H
