#ifndef MAKECOMMENTORPOST_H
#define MAKECOMMENTORPOST_H

#include <QDialog>

namespace Ui {
class makeCommentOrPost;
}

class makeCommentOrPost : public QDialog
{
    Q_OBJECT

public:
    explicit makeCommentOrPost(QWidget *parent = nullptr);
    ~makeCommentOrPost();

private slots:
    void on_pushButton_clicked();

private:
    Ui::makeCommentOrPost *ui;
};

#endif // MAKECOMMENTORPOST_H
