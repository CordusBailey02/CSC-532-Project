#ifndef COMMUNITIESTAB_H
#define COMMUNITIESTAB_H

#include <QDialog>
#include <QtWidgets>

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
};

#endif // COMMUNITIESTAB_H
