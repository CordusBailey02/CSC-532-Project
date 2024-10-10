#ifndef COMMENT_1_H
#define COMMENT_1_H

#include <QDialog>

namespace Ui {
class comment_1;
}

class comment_1 : public QDialog
{
    Q_OBJECT

public:
    explicit comment_1(QWidget *parent = nullptr);
    ~comment_1();

private:
    Ui::comment_1 *ui;
};

#endif // COMMENT_1_H
