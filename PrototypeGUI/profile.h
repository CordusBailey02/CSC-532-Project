#ifndef PROFILE_H
#define PROFILE_H

#include "post_1.h"
#include "comment_1.h"
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

private:
    Ui::Profile *ui;
    Post_1 *post_3;
    comment_1 *comment_3;
};

#endif // PROFILE_H
