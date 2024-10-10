#ifndef POST_1_H
#define POST_1_H

#include <QDialog>
#include "comment_1.h"
#include "makecommentorpost.h"
#include <QtWidgets>

namespace Ui {
class Post_1;
}

class Post_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Post_1(QWidget *parent = nullptr);
    ~Post_1();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::Post_1 *ui;
    comment_1 *comment;
    makeCommentOrPost *makeCommentOrPost_1;
};

#endif // POST_1_H
