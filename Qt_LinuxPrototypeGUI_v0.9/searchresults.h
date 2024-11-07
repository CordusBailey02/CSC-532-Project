#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QDialog>
#include <QtWidgets>

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

    void on_listWidget_answersFromSearch_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::searchResults *ui;
};

#endif // SEARCHRESULTS_H
