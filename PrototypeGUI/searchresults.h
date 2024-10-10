#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include "communitiestab.h"
#include "post_1.h"
#include "comment_1.h"
#include <QDialog>

namespace Ui {
class searchResults;
}

class searchResults : public QDialog
{
    Q_OBJECT

public:
    explicit searchResults(QWidget *parent = nullptr);
    ~searchResults();

private slots:
    void on_listWidget_communitiesFromSearch_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_postsFromSearch_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_commentsFromSearch_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::searchResults *ui;
    Post_1 *post_4;
    comment_1 *comment_4;
    communitiesTab *communitiesTab_4;
};

#endif // SEARCHRESULTS_H
