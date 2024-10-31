#ifndef ACCOUNTCODE_H
#define ACCOUNTCODE_H

#include <QDialog>

namespace Ui {
class AccountCode;
}

class AccountCode : public QDialog
{
    Q_OBJECT

public:
    explicit AccountCode(QWidget *parent = nullptr);
    ~AccountCode();

private slots:
    void on_pushButton_submitCode_clicked();

private:
    Ui::AccountCode *ui;
};

#endif // ACCOUNTCODE_H
