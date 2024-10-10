#ifndef COMMUNITIESTAB_H
#define COMMUNITIESTAB_H

#include "post_1.h"
#include <QDialog>

namespace Ui {
class communitiesTab;
}

class communitiesTab : public QDialog
{
    Q_OBJECT

public:
    explicit communitiesTab(QWidget *parent = nullptr);
    ~communitiesTab();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::communitiesTab *ui;
    Post_1 *post_2;
};

#endif // COMMUNITIESTAB_H
