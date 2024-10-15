#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private slots:
    void on_listWidget_postsFromProfile_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_commentsFromProfile_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_answersFromProfile_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_LinkedInLine_returnPressed();

private:
    Ui::Profile *ui;
};

#endif // PROFILE_H
