#ifndef POST_1_H
#define POST_1_H

#include <QDialog>

namespace Ui {
class Post_1;
}

class Post_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Post_1(QWidget *parent = nullptr);
    ~Post_1();

private:
    Ui::Post_1 *ui;
};

#endif // POST_1_H
