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
    void on_pushButton_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_3_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_3_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
