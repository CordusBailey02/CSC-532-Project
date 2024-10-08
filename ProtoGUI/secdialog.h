#ifndef SECDIALOG_H
#define SECDIALOG_H

#include "profile.h"
#include "post_1.h"
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

private:
    Ui::SecDialog *ui;
    Profile *profile;
    Post_1 *post;
};

#endif // SECDIALOG_H
