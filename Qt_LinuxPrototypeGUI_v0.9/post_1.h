#ifndef POST_1_H
#define POST_1_H

#include <QDialog>
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

    void on_pushButton_upPost_clicked();

    void on_pushButton_downPost_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Post_1 *ui;
};

#endif // POST_1_H
